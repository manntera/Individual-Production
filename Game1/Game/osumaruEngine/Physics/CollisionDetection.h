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
	void Init(const ICollider* collider, const D3DXVECTOR3& position, const D3DXQUATERNION& rotation);

	/*
	���W��ݒ�
	*/
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
		m_rigidBody.SetPosition(position);
	}

	/*
	��]��ݒ�
	*/
	void SetRotation(const D3DXQUATERNION& rotation)
	{
		m_rotation = rotation;
		m_rigidBody.SetRotation(m_rotation);
	}

	//���s
	void Execute();

	/*
	�������Ă邩�H
	true�Ȃ瓖�����Ă�Bfalse�Ȃ瓖�����ĂȂ�
	*/
	bool IsHit() const
	{
		return m_isHit;
	}

	/*
	UserIndex�̐ݒ�
	userIndex�@		�ݒ肵����UserIndex�̔ԍ�
	*/
	void SetUserIndex(int userIndex)
	{
		m_rigidBody.SetUserIndex(userIndex);
	}

	//���������I�u�W�F�N�g�̖@�����擾
	const D3DXVECTOR3& GetCollisionNormal() const
	{
		return m_hitCollisionNormal;
	}

	//��]���擾
	const D3DXQUATERNION& GetRotation() const
	{
		return m_rotation;
	}

	//���W���擾
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}

	//�q�b�g�����R���W�����̑������擾
	int GetHitCollisionType() const
	{
		return m_collisionType;
	}

	//���̃R���W�����̑�����ݒ�
	void SetJudgmentType(int judgmentType)
	{
		m_judgmentType = judgmentType;
	}
private:
	RigidBody				m_rigidBody;			//����
	const ICollider*		m_pCollider;			//�R���C�_�[
	D3DXVECTOR3				m_position;				//���W
	D3DXQUATERNION			m_rotation;				//��]
	bool					m_isHit;				//�������Ă邩�H
	D3DXVECTOR3				m_hitCollisionNormal;	//�e�X�g�p
	int						m_collisionType;		//�q�b�g�����ؼޮ݂̑���
	int						m_judgmentType;			//���̃R���W�����̑���
};