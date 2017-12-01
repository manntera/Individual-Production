#pragma once
#include "Texture.h"


class Primitive : Uncopyable
{
public:
	enum EnFormatIndex
	{
		enIndex16,
		enIndex32,
	};

	enum EnPrimitiveType
	{
		enTypeLineList,
		enTypeTriangleStrip,
		enTypeTriangleList,
	};

	//コンストラクタ
	Primitive();

	//デストラクタ
	~Primitive();

	/*
	プリミティブを作る関数
	vertexLayout		頂点定義のレイアウト
	vertexBuffer		頂点バッファ
	vertexNum			頂点数
	vertexStride		頂点データのサイズ
	indexBuffer			インデックスバッファ
	indexNum			インデックス数
	indexFormat			インデックスバッファのフォーマット
	primitiveType		プリミティブの種類
	*/
	void Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum,  int vertexStride, void *indexBuffer, int indexNum, EnFormatIndex indexFormat, EnPrimitiveType primitivetype );

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

	//頂点定義を取得
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDecaration()
	{
		return m_pVertexDecaration;
	}

	int GetPolygonNum()
	{
		return m_polygonNum;
	}

	int GetVertexStride()
	{
		return m_vertexStride;
	}

	D3DPRIMITIVETYPE GetPrimitiveType()
	{
		return m_primitiveType;
	}

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//頂点バッファ
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//頂点定義
	int								m_vertexNum;			//頂点数
	D3DPRIMITIVETYPE				m_primitiveType;
	int								m_polygonNum;
	int								m_vertexStride;
};		