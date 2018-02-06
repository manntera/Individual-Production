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
	const LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() const
	{
		return m_pVertexBuffer;
	}

	//インデックスバッファを取得。
	const LPDIRECT3DINDEXBUFFER9 GetIndexBuffer() const
	{
		return m_pIndexBuffer;
	}
	//頂点数を取得。
	int GetVertexNum() const
	{
		return m_vertexNum;
	}
	//リリース
	void Release();

	//頂点定義を取得
	const LPDIRECT3DVERTEXDECLARATION9 GetVertexDecaration() const
	{
		return m_pVertexDecaration;
	}

	//ポリゴン数を取得
	int GetPolygonNum() const
	{
		return m_polygonNum;
	}

	//頂点ストライドを取得
	int GetVertexStride() const
	{
		return m_vertexStride;
	}

	//プリミティブタイプを取得
	D3DPRIMITIVETYPE GetPrimitiveType() const
	{
		return m_primitiveType;
	}

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//頂点バッファ
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//頂点定義
	int								m_vertexNum;			//頂点数
	D3DPRIMITIVETYPE				m_primitiveType;		//プリミティブの種類
	int								m_polygonNum;			//ポリゴン数
	int								m_vertexStride;			//頂点ストライド
};		