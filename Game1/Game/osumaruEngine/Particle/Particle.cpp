#include "engineStdafx.h"
#include "Particle.h"
#include "../Graphics/VertexCommon.h"
#include "../Engine.h"
#include "../Graphics/EffectManager.h"
#include "../Physics/CharacterController.h"
#include "../Camera.h"
#include "ParticleEmitter.h"

Particle::Particle()
{
	m_pEffect = nullptr;
	m_lifeTimer = 0.0f;
	m_size = { 1.0f, 1.0f};
	m_speed = { 0.0f, 0.0f, 0.0f };
	m_camera = nullptr;
}

Particle::~Particle()
{
	m_primitive.Release();
}

void Particle::Init(SParticleEmittInfo& info, Camera* camera)
{
	m_gravity = info.gravity;
	m_camera = camera;
	m_position = info.emitterPosition;
	D3DXVECTOR3 addPos = info.randomPosition;
	addPos.x *= (float)GetRandom().GetRandDouble() * 2.0f - 1.0f;
	addPos.y *= (float)GetRandom().GetRandDouble() * 2.0f - 1.0f;
	addPos.z *= (float)GetRandom().GetRandDouble() * 2.0f - 1.0f;
	m_position += addPos;
	m_lifeTimer = info.lifeTime;
	m_texture = GetTextureResource().LoadTexture(info.filePath);
	//頂点バッファを作成
	VERTEX_PT elements[4] =
	{
		{ -1.0f,	1.0f,		0.0f,	1.0f,	info.uv.x ,	info.uv.y },
		{ 1.0f,		1.0f,		0.0f,	1.0f,	info.uv.z ,	info.uv.y },
		{ 1.0f,		-1.0f,		0.0f,	1.0f,	info.uv.z ,	info.uv.w },
		{ -1.0f,	-1.0f,		0.0f,	1.0f,	info.uv.x ,	info.uv.w },
	};
	//インデックスバッファーを作成
	WORD indexElements[6] = { 0, 2, 3, 0, 1, 2 };
	//プリミティブを作成
	m_primitive.Create(vertex_PT, elements, 4, sizeof(VERTEX_PT), indexElements, 6, Primitive::enIndex16, Primitive::enTypeTriangleList);
	D3DXMatrixIdentity(&m_worldMatrix);
	m_pEffect = GetEffectManager().LoadEffect("Assets/shader/particle.fx");
	D3DXQuaternionIdentity(&m_rotation);

	m_size.x = info.width;
	m_size.y = info.height;
}

void Particle::Update()
{
	m_speed += m_gravity * GetGameTime().GetDeltaFrameTime();
	m_position += m_speed;
	m_lifeTimer -= GetGameTime().GetDeltaFrameTime();
	if (m_lifeTimer < 0.0f)
	{
		Delete(this);
	}
	D3DXQUATERNION multi;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_angle);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	D3DXMATRIX cameraRotMat;
	cameraRotMat = m_camera->GetViewMatrix();
	D3DXMatrixInverse(&cameraRotMat, NULL, &cameraRotMat);
	cameraRotMat.m[3][0] = 0.0f;
	cameraRotMat.m[3][1] = 0.0f;
	cameraRotMat.m[3][2] = 0.0f;
	cameraRotMat.m[3][3] = 1.0f;
	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, m_size.x, m_size.y, 1.0f);
	D3DXMATRIX rotationMat;
	D3DXMatrixRotationQuaternion(&rotationMat, &m_rotation);
	D3DXMATRIX transMat;
	D3DXMatrixTranslation(&transMat, m_position.x, m_position.y, m_position.z);


	D3DXMatrixIdentity(&m_worldMatrix);

	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &scaleMat);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &cameraRotMat);
	//D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &rotationMat);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &transMat);
}

void Particle::Draw()
{
	D3DXMATRIX worldViewProjMat;
	D3DXMatrixMultiply(&worldViewProjMat, &m_worldMatrix, &m_camera->GetViewMatrix());
	D3DXMatrixMultiply(&worldViewProjMat, &worldViewProjMat, &m_camera->GetProjectionMatrix());
	LPDIRECT3DDEVICE9& pD3DDevice = GetEngine().GetDevice();
	DWORD srcBackup, destBackup, alphaBlendBackup, alphaTestBackup, alphaRefBackup, alphaFuncBackup;;
	pD3DDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &alphaBlendBackup);
	pD3DDevice->GetRenderState(D3DRS_SRCBLEND, &srcBackup);
	pD3DDevice->GetRenderState(D3DRS_DESTBLEND, &destBackup);
	pD3DDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &alphaTestBackup);
	pD3DDevice->GetRenderState(D3DRS_ALPHAREF, &alphaRefBackup);
	pD3DDevice->GetRenderState(D3DRS_ALPHAFUNC, &alphaTestBackup);
	
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//描画
	m_pEffect->SetTechnique("Particle");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	m_pEffect->SetTexture("g_tex", m_texture->GetBody());
	m_pEffect->SetMatrix("g_world", &worldViewProjMat);
	m_pEffect->CommitChanges();
	pD3DDevice->SetVertexDeclaration(m_primitive.GetVertexDecaration());
	pD3DDevice->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, sizeof(VERTEX_PT));
	pD3DDevice->SetIndices(m_primitive.GetIndexBuffer());
	pD3DDevice->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());

	m_pEffect->EndPass();
	m_pEffect->End();

	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaBlendBackup);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, srcBackup);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, destBackup);
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, alphaTestBackup);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, alphaRefBackup);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,alphaTestBackup);
}