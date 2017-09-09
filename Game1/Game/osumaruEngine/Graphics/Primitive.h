#pragma once
#include "Texture.h"

class Primitive
{
public:

	//コンストラクタ
	Primitive();

	//デストラクタ
	~Primitive();

	//
	void Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum,  int vertexStride, WORD *indexBuffer, int indexNum);

	//頂点バッファを取得。
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}

	//インデックスバッファを取得。
	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	//頂点数を取得。
	int GetVertexNum()
	{
		return m_vertexNum;
	}
	//リリース
	void Release();
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//頂点バッファ
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//頂点定義
	int								m_vertexNum;			//頂点数
};		