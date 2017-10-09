#include "engineStdafx.h"
#include "Sprite.h"
#include "../Engine.h"
#include "VertexCommon.h"
#include "EffectManager.h"

Sprite::Sprite()
{
	m_alpha = 1.0f;
}

Sprite::~Sprite()
{
	Release();
}

void Sprite::Init(char *filePath)
{
	Release();
	//�e�N�X�`����ǂݍ���
	m_texture.Load(filePath);

	//�X�v���C�g�̍��W��������
	float centerPosx = m_texture.GetWidth() / 2.0f;
	float centerPosy = m_texture.GetHeight() / 2.0f;
	m_centerPosition = { centerPosx, centerPosy};
	SetPosition({ 0.0f, 0.0f});

	//�G�t�F�N�g�����[�h
	m_pEffect = GetEngine().GetEffectManager()->LoadEffect("Assets/shader/sprite.fx");
	//���_�o�b�t�@���쐬
	VERTEX_PT elements[4] =
	{
		{ -1.0f,	1.0f,	0.0f,	1.0f,	0.0f ,	0.0f },
		{ 1.0f,		1.0f,	0.0f,	1.0f,	1.0f ,	0.0f },
		{ 1.0f,		-1.0f,	0.0f,	1.0f,	1.0f ,	1.0f },
		{ -1.0f,	-1.0f,	0.0f,	1.0f,	0.0f ,	1.0f },
	};
	//�C���f�b�N�X�o�b�t�@�[���쐬
	WORD indexElements[6] = { 0, 2, 3, 0, 1, 2 };
	//�v���~�e�B�u���쐬
	m_primitive.Create(vertex_PT, elements, 4, sizeof(VERTEX_PT), indexElements, 6);

	m_size.x = m_texture.GetWidth();
	m_size.y = m_texture.GetHeight();
}

void Sprite::Draw()
{
	//���W�̃X�P�[����ϊ�
	D3DXVECTOR3 position;
	position.x = m_position.x / FRAME_BUFFER_WIDTH;
	position.y = m_position.y / FRAME_BUFFER_HEIGHT;
	position.z = 0.0f;
	//�g��̃X�P�[����ϊ�
	D3DXVECTOR3 size;
	size.x = m_size.x / FRAME_BUFFER_WIDTH;
	size.y = m_size.y / FRAME_BUFFER_HEIGHT;
	size.z = 0.0f;

	//�ړ��s����쐬
	D3DXMATRIX transform;
	D3DXMatrixTranslation(&transform, position.x, position.y, position.z);
	//�g��s����쐬
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	//���[���h�s����쐬
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scale);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &transform);
	LPDIRECT3DDEVICE9& pD3DDevice = GetEngine().GetDevice();
	DWORD srcBackup;
	DWORD destBackup;
	DWORD cullModeBackup;
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->GetRenderState(D3DRS_SRCBLEND, &srcBackup);
	pD3DDevice->GetRenderState(D3DRS_DESTBLEND, &destBackup);
	pD3DDevice->GetRenderState(D3DRS_CULLMODE, &cullModeBackup);

	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	m_pEffect->SetTechnique("Sprite");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	m_pEffect->SetTexture("g_tex", m_texture.GetBody());
	m_pEffect->SetValue("g_world", worldMatrix, sizeof(worldMatrix));
	m_pEffect->SetFloat("g_alpha", m_alpha);
	m_pEffect->CommitChanges();
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pD3DDevice->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, sizeof(VERTEX_PT));
	pD3DDevice->SetIndices(m_primitive.GetIndexBuffer());
	pD3DDevice->SetFVF(D3DFVF_XYZW | D3DFVF_TEX1);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();

	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//pD3DDevice->SetRenderState(D3DRS_SRCBLEND, srcBackup); 
	//pD3DDevice->SetRenderState(D3DRS_DESTBLEND, destBackup);
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, cullModeBackup);

}

void Sprite::Release()
{
	m_texture.Release();
	m_primitive.Release();
}