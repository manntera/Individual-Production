#pragma once
#include "ICollider.h"
//���̃R���C�_�[

class BoxCollider : public ICollider
{
public:
	//�R���X�g���N�^
	BoxCollider();

	//�f�X�g���N�^
	~BoxCollider();
	
	/*
	�R���C�_�[�̏�����
	box		�{�b�N�X�̃T�C�Y
	*/
	void Create(btVector3 box)
	{
		m_boxShape = new btBoxShape(box);
	}

	//�R���C�_�[���擾
	btCollisionShape* GetBody()override
	{
		return m_boxShape;
	}
private:
	btBoxShape*		m_boxShape;//�R���C�_�[
};
