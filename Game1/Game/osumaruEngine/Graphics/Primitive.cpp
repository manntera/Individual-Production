#include "Primitive.h"
#include "../Engine.h"
#include "EffectManager.h"
#include "VertexCommon.h"


void Primitive::Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum, int vertexStride, WORD *indexBuffer, int indexNum)
{
	m_vertexNum = vertexNum;
	LPDIRECT3DDEVICE9& pD3DDevice = GetEngine().GetDevice();
	pD3DDevice->CreateVertexBuffer(
		m_vertexNum * vertexStride,
		0,
		0,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		NULL
	);
	pD3DDevice->CreateVertexDeclaration(vertexLayout, &m_pVertexDecaration);
	void* pVertex;
	m_pVertexBuffer->Lock(0, 0, &pVertex, 0);
	memcpy(pVertex, vertexBuffer, m_vertexNum * vertexStride);
	m_pVertexBuffer->Unlock();
	pD3DDevice->CreateIndexBuffer(
		sizeof(WORD) * indexNum,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		NULL
	);
	void* pIndex;
	m_pIndexBuffer->Lock(0, 0, &pIndex, 0);
	memcpy(pIndex, indexBuffer, sizeof(WORD) * indexNum);
	m_pIndexBuffer->Unlock();
}

