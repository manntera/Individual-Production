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
	const btCollisionShape* GetBody() const override
	{
		return m_meshShape.get();
	}

	const D3DXVECTOR3& GetAabbMax() const
	{
		return m_aabbMax;
	}

	const D3DXVECTOR3& GetAabbMin() const
	{
		return m_aabbMin;
	}
private:
	typedef std::vector<D3DXVECTOR3>					VertexBuffer;		//頂点バッファ
	typedef std::vector<unsigned int>					IndexBuffer;		//インデックスバッファ
	std::vector<VertexBuffer*>							m_vertexBufferArray;		//頂点バッファの配列
	std::vector<IndexBuffer*>							m_indexBufferArray;		//インデックスバッファの配列
	D3DXVECTOR3											m_aabbMax;
	D3DXVECTOR3											m_aabbMin;
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//メッシュコライダー
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;

};
