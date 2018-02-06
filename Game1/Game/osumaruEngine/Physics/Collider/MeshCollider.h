#pragma once
#include "ICollider.h"
class SkinModel;

//���b�V���R���C�_�[
class MeshCollider : public ICollider
{
public:
	//�R���X�g���N�^
	MeshCollider();

	//�f�X�g���N�^
	~MeshCollider();

	/*
	���f�����烁�b�V������鏉�����֐�
	model			���b�V���̌��ƂȂ郂�f��
	offsetMatrix	�}�g���b�N�X
	*/
	void CreateFromSkinModel(SkinModel* model, const D3DXMATRIX* offsetMatrix);

	//�R���C�_�[���擾�B
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
	typedef std::vector<D3DXVECTOR3>					VertexBuffer;		//���_�o�b�t�@
	typedef std::vector<unsigned int>					IndexBuffer;		//�C���f�b�N�X�o�b�t�@
	std::vector<VertexBuffer*>							m_vertexBufferArray;		//���_�o�b�t�@�̔z��
	std::vector<IndexBuffer*>							m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��
	D3DXVECTOR3											m_aabbMax;
	D3DXVECTOR3											m_aabbMin;
	std::unique_ptr<btBvhTriangleMeshShape>				m_meshShape;				//���b�V���R���C�_�[
	std::unique_ptr<btTriangleIndexVertexArray>			m_stridingMeshInterface;

};
