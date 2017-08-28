#include "Sprite.h"
#include "../Engine.h"
#include "Texture.h"
#include "VertexCommon.h"
#include "EffectManager.h"

Sprite::Sprite()
{
	m_pTexture = nullptr;
}

Sprite::~Sprite()
{
	if (m_pTexture != nullptr)
	{
		delete m_pTexture;
	}
}

void Sprite::Init(char *filePath)
{
	m_pTexture = new Texture;
	m_pTexture->Load(filePath);
	float centerPosx = m_pTexture->GetWidth() / 2.0f;
	float centerPosy = m_pTexture->GetHeight() / 2.0f;


	m_centerPosition = { centerPosx, centerPosy};
	SetPosition({ 0.0f, 0.0f});

	m_pEffect = GetEngine().GetEffectManager()->LoadEffect("../Game/Assets/shader/sprite.fx");
	float width = m_pTexture->GetWidth();
	float height = m_pTexture->GetHeight();
	VERTEX_PT elements[4] =
	{
		{ -0.5f,	0.5f,	0.0f,	1.0f,	0.0f ,	0.0f },
		{ 0.5f,		0.5f,	0.0f,	1.0f,	1.0f ,	0.0f },
		{ 0.5f,		-0.5f,	0.0f,	1.0f,	1.0f ,	1.0f },
		{ -0.5f,	-0.5f,	0.0f,	1.0f,	0.0f ,	1.0f },
	};

	WORD indexElements[6] = { 0, 2, 3, 0, 1, 2 };
	m_primitive.Create(vertex_PT, elements, 4, sizeof(VERTEX_PT), indexElements, 6);
	m_size.x = m_pTexture->GetWidth();
	m_size.y = m_pTexture->GetHeight();
}

void Sprite::Draw()
{
	float windowWidthHalf = FRAME_BUFFER_WIDTH / 2;
	float windowHeightHalf = FRAME_BUFFER_HEIGHT / 2;
	//座標のスケールを変換
	D3DXVECTOR3 position;
	position.x = m_position.x / windowWidthHalf;
	position.y = m_position.y / windowHeightHalf;
	position.z = 0.0f;
	//拡大のスケールを変換
	D3DXVECTOR3 size;
	size.x = m_size.x / windowWidthHalf;
	size.y = m_size.y / windowHeightHalf;
	size.z = 0.0f;

	//移動行列を作成
	D3DXMATRIX transform;
	D3DXMatrixTranslation(&transform, position.x, position.y, position.z);
	//拡大行列を作成
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	//ワールド行列を作成
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scale);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &transform);
	LPDIRECT3DDEVICE9& pD3DDevice = GetEngine().GetDevice();
	m_pEffect->SetTechnique("Sprite");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	m_pEffect->SetTexture("g_tex", m_pTexture->GetBody());
	m_pEffect->SetValue("g_world", worldMatrix, sizeof(worldMatrix));
	m_pEffect->CommitChanges();
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pD3DDevice->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, sizeof(VERTEX_PT));
	pD3DDevice->SetIndices(m_primitive.GetIndexBuffer());
	pD3DDevice->SetFVF(D3DFVF_XYZW | D3DFVF_TEX1);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();
}

