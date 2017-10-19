#pragma once
#include "RigidBody.h"
//�����蔻������N���X

class CollisionDetection
{
public:

	//�R���X�g���N�^
	CollisionDetection();
	
	//�f�X�g���N�^
	~CollisionDetection();

	/*
	�������֐�
	colldier	�R���C�_�[
	position	���W
	rotation	��]
	*/
	void Init(ICollider* collider, D3DXVECTOR3 position, D3DXQUATERNION rotation);

	/*
	���W��ݒ�
	*/
	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
		m_rigidBody.GetBody()->getWorldTransform().setOrigin({ position.x, position.y, position.z });
	}

	/*
	��]��ݒ�
	*/
	void SetRotation(D3DXQUATERNION rotation)
	{
		m_rotation = rotation;
		m_rigidBody.GetBody()->getWorldTransform().setRotation({ m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w });
	}

	//���s
	void Execute();

	/*
	�������Ă邩�H
	true�Ȃ瓖�����Ă�Bfalse�Ȃ瓖�����ĂȂ�
	*/
	bool IsHit()
	{
		return m_isHit;
	}

	/*
	UserIndex�̐ݒ�
	userIndex�@		�ݒ肵����UserIndex�̔ԍ�
	*/
	void SetUserIndex(int userIndex)
	{
		m_rigidBody.GetBody()->setUserIndex(userIndex);
	}

	D3DXVECTOR3 GetHitCOllisionNormal()
	{
		return m_hitCollisionNormal;
	}

private:
	RigidBody		m_rigidBody;		//����
	ICollider*		m_pCollider;		//�R���C�_�[
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	bool			m_isHit;			//�������Ă邩�H
	D3DXVECTOR3		m_hitCollisionNormal;
};