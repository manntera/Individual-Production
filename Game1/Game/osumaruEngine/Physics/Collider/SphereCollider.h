#pragma once
#include "ICollider.h"
//���`��̃R���C�_�[�N���X

class SphereCollider : public ICollider
{
public:

	//�R���X�g���N�^
	SphereCollider();
	
	//�f�X�g���N�^
	~SphereCollider();

	/*
	�R���C�_�[���쐬
	radius		���̔��a
	*/
	void Create(float radius);

	//�R���C�_�[���擾
	btSphereShape* GetBody()override
	{
		return m_sphereShape;
	}

private:
	btSphereShape* m_sphereShape;	//���̃R���C�_�[
};