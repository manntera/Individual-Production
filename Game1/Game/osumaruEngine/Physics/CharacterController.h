#pragma once

#include "Collider\CapsuleCollider.h"
#include "RigidBody.h"


const float cPI = 3.14159265358979323846f;

//�L�����N�^�[�R���g���[���[
//�Փˉ����ƏՓ˔�������Ă����N���X�B

class CharacterController
{
public:
	//�R���X�g���N�^
	CharacterController();

	//�f�X�g���N�^
	~CharacterController();

	/*
	�������֐�
	float		radius		�L�����N�^�[�̔��a�@�@�@
	float		height		�L�����N�^�[�̍����@
	D3DXVECTOR3 position	�L�����̍��W

	�R���C�_�[�̓J�v�Z���R���C�_�[�ŃL�����N�^�[�̌��_�������ɂ��邱�Ƃ�O��Ƃ��Ă���B
	*/
	void Init(float radius, float height, const D3DXVECTOR3& position);

	//���s�֐�
	void Execute();

	//���W���擾�B
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}

	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_position = pos;
	}

	//�ړ����x��ݒ�B
	void SetMoveSpeed(D3DXVECTOR3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
		//������Ɉړ����x���^�����Ă����ꍇ�W�����v����Ƃ݂Ȃ�
		if (m_moveSpeed.y > 0.0f)
		{
			Jump();
		}
	}
	
	//�ړ����x���擾�B
	D3DXVECTOR3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}

	//�W�����v����Ƃ��ɌĂ΂��֐��B
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}

	//�W�����v���Ă��邩�H
	bool IsJump() const
	{
		return m_isJump;
	}

	//�n�ʂɐڒn���Ă��邩�H
	bool IsOnGround()
	{
		return m_isOnGround;
	}

	//�R���C�_�[���擾�B
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}

	//�d�͂�ݒ�B
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}

	float GetGravity()
	{
		return m_gravity;
	}

	//���̂��폜�B
	void RemovedRigidBody();

	const btCollisionObject* GetGroundCollisionObject()
	{
		return m_groundHitObject;
	}

	const btCollisionObject* GetWallCollisionObject()
	{
		return m_wallHitObject;
	}

	D3DXVECTOR3 GetWallNormal()
	{
		return m_wallNormal;
	}

	void SetUserIndex(int userNum)
	{
		m_rigidBody.GetBody()->setUserIndex(userNum);
	}

	void StaticExecute();

	void DynamicExecute();

	void Draw();

private:
	D3DXVECTOR3		m_position;			//���W
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x
	bool			m_isJump;			//�W�����v���Ă��邩�H
	bool			m_isOnGround;		//�n�ʂɐݒu���Ă��邩�H
	CapsuleCollider	m_collider;			//�R���C�_�[
	float			m_radius;			//���a
	float			m_height;			//����
	RigidBody		m_rigidBody;		//����
	float			m_gravity;			//�d��
	const btCollisionObject* m_groundHitObject;
	const btCollisionObject* m_wallHitObject;
	D3DXVECTOR3		m_wallNormal;
};