#include "engineStdafx.h"
#include "Primitive.h"
#include "../Engine.h"
#include "EffectManager.h"
#include "VertexCommon.h"


Primitive::Primitive()
{
	m_pIndexBuffer = nullptr;
	m_pVertexBuffer = nullptr;
	m_pVertexDecaration = nullptr;
	m_vertexNum = 0;
}

Primitive::~Primitive()
{
	Release();
}

void Primitive::Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum, int vertexStride, WORD *indexBuffer, int indexNum)
{
	Release();
	m_vertexNum = vertexNum;
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9& pD3DDevice = GetEngine().GetDevice();
	//���_�o�b�t�@���쐬
	pD3DDevice->CreateVertexBuffer(
		m_vertexNum * vertexStride,
		0,
		0,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		NULL
	);
	//���C�A�E�g�����Ƃɒ��_��`���쐬�B
	pD3DDevice->CreateVertexDeclaration(vertexLayout, &m_pVertexDecaration);
	//��������_�o�b�t�@�ɏ������݁B
	void* pVertex;
	m_pVertexBuffer->Lock(0, 0, &pVertex, 0);
	memcpy(pVertex, vertexBuffer, m_vertexNum * vertexStride);
	m_pVertexBuffer->Unlock();
	//�C���f�b�N�X�o�b�t�@���쐬
	pD3DDevice->CreateIndexBuffer(
		sizeof(WORD) * indexNum,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		NULL
	);
	//������C���f�b�N�X�o�b�t�@�ɏ������݁B
	void* pIndex;
	m_pIndexBuffer->Lock(0, 0, &pIndex, 0);
	memcpy(pIndex, indexBuffer, sizeof(WORD) * indexNum);
	m_pIndexBuffer->Unlock();
}

void Primitive::Release()
{
	if (m_pIndexBuffer != nullptr)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}
	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
	if (m_pVertexDecaration != nullptr)
	{
		m_pVertexDecaration->Release();
		m_pVertexDecaration = nullptr;
	}
}