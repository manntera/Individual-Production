#pragma once
#include "ICollider.h"
class SkinModel;

//メッシュコライダー
class MeshCollider : public ICollider
{
public:
	MeshCollider();

	~MeshCollider();

	void CreateFromSkinModel(SkinModel* model, const D3DXMATRIX* offsetMatrix);


	btCollisionShape* GetBody() override
	{
		return meshShape;
	}
private:
	typedef std::vector<D3DXVECTOR3>	VertexBuffer;		//頂点バッファ
	typedef std::vector<unsigned int>	IndexBuffer;		//ｲﾝﾃﾞｯｸｽバッファ
	std::vector<VertexBuffer*>		vertexBufferArray;
	std::vector<IndexBuffer*>		indexBufferArray;
	btBvhTriangleMeshShape*			meshShape;
	btTriangleIndexVertexArray*		stridingMeshInterface;

};
