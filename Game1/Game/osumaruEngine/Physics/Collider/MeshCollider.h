#pragma once
#include "ICollider.h"
class SkinModel;

//メッシュコライダー
class MeshCollider : public ICollider
{
public:
	//コンストラクタ
	MeshCollider();

	//デストラクタ
	~MeshCollider();

	/*
	モデルからメッシュを作る初期化関数
	model			メッシュの元となるモデル
	offsetMatrix	マトリックス
	*/
	void CreateFromSkinModel(SkinModel* model, const D3DXMATRIX* offsetMatrix);

	//コライダーを取得。
	btCollisionShape* GetBody() override
	{
		return m_meshShape;
	}

	D3DXVECTOR3 GetAabbMax()
	{
		return m_aabbMax;
	}

	D3DXVECTOR3 GetAabbMin()
	{
		return m_aabbMin;
	}
private:
	typedef std::vector<D3DXVECTOR3>	VertexBuffer;		//頂点バッファ
	typedef std::vector<unsigned int>	IndexBuffer;		//インデックスバッファ
	std::vector<VertexBuffer*>		m_vertexBufferArray;		//頂点バッファの配列
	std::vector<IndexBuffer*>		m_indexBufferArray;		//インデックスバッファの配列
	D3DXVECTOR3						m_aabbMax;
	D3DXVECTOR3						m_aabbMin;
	btBvhTriangleMeshShape*			m_meshShape;				//メッシュコライダー
	btTriangleIndexVertexArray*		m_stridingMeshInterface;

};
