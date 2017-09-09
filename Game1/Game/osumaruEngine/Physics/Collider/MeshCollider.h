#pragma once
#include "ICollider.h"
class SkinModel;

//���b�V���R���C�_�[
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
	typedef std::vector<D3DXVECTOR3>	VertexBuffer;		//���_�o�b�t�@
	typedef std::vector<unsigned int>	IndexBuffer;		//���ޯ���o�b�t�@
	std::vector<VertexBuffer*>		vertexBufferArray;
	std::vector<IndexBuffer*>		indexBufferArray;
	btBvhTriangleMeshShape*			meshShape;
	btTriangleIndexVertexArray*		stridingMeshInterface;

};
