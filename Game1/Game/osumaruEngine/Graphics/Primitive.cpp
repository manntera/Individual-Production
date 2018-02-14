#include "engineStdafx.h"
#include "Primitive.h"
#include "../Engine.h"
#include "EffectManager.h"
#include "VertexCommon.h"


Primitive::Primitive() :
	m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr),
	m_pVertexDecaration(nullptr),
	m_vertexNum(0),
	m_primitiveType(D3DPT_LINELIST),
	m_polygonNum(0),
	m_vertexStride(0)

{
}

Primitive::~Primitive()
{
	Release();
}

void Primitive::Create(const D3DVERTEXELEMENT9 *vertexLayout, const void *vertexBuffer, int vertexNum, int vertexStride,const void *indexBuffer, int indexNum, EnFormatIndex indexFormat, EnPrimitiveType primitiveType)
{
	Release();
	m_vertexNum = vertexNum;
	//デバイスを取得
	LPDIRECT3DDEVICE9& pD3DDevice = GetEngine().GetDevice();
	//頂点バッファを作成
	pD3DDevice->CreateVertexBuffer(
		m_vertexNum * vertexStride,
		0,
		0,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		NULL
	);
	//レイアウトをもとに頂点定義を作成。
	pD3DDevice->CreateVertexDeclaration(vertexLayout, &m_pVertexDecaration);
	//作った頂点バッファに書き込み。
	void* pVertex;
	m_pVertexBuffer->Lock(0, 0, &pVertex, 0);
	memcpy(pVertex, vertexBuffer, m_vertexNum * vertexStride);
	m_pVertexBuffer->Unlock();
	D3DFORMAT format;
	int size;
	switch (indexFormat)
	{
	case enIndex16:
		format = D3DFMT_INDEX16;
		size = sizeof(WORD);
		break;

	case enIndex32:
		format = D3DFMT_INDEX32;
		size = sizeof(DWORD);
		break;
	}
	//インデックスバッファを作成
	pD3DDevice->CreateIndexBuffer(
		size * indexNum,
		0,
		format,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		NULL
	);
	//作ったインデックスバッファに書き込み。
	void* pIndex;
	m_pIndexBuffer->Lock(0, 0, &pIndex, 0);
	memcpy(pIndex, indexBuffer, size * indexNum);
	m_pIndexBuffer->Unlock();

	switch (primitiveType)
	{
	case enTypeLineList:
		m_polygonNum = indexNum / 2;
		m_primitiveType = D3DPT_LINELIST;
		break;
	case enTypeTriangleList:
		m_polygonNum = indexNum / 3;
		m_primitiveType = D3DPT_TRIANGLELIST;
		break;
	case enTypeTriangleStrip:
		m_polygonNum = indexNum - 2;
		m_primitiveType = D3DPT_TRIANGLESTRIP;
		break;
	}
	m_vertexStride = vertexStride;
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