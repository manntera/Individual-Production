#pragma once
#include "ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	//�R���X�g���N�^
	CapsuleCollider();

	//�f�X�g���N�^
	~CapsuleCollider();

	/*
	�R���C�_�[����鏉�����֐�
	radius		�R���C�_�[�̔��a
	height		�R���C�_�[�̍���
	*/
	void Create(float radius, float height)
	{
		m_shape = new btCapsuleShape(radius, height);
	}

	//�R���C�_�[���擾
	btCollisionShape* GetBody()override
	{
		return m_shape;
	}

private:
	btCapsuleShape*		m_shape;	//�R���C�_�[
};