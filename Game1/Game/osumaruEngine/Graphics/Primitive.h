#pragma once
#include "Texture.h"

class Primitive
{
public:
	void Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum,  int vertexStride, WORD *indexBuffer, int indexNum);

	//頂点バッファのゲッター
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}

	//インデックスバッファのゲッター
	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	//頂点数のゲッター
	int GetVertexNum()
	{
		return m_vertexNum;
	}
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;
	int								m_vertexNum;
};		