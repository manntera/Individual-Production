#pragma once
class ICollider;

//���̏��
struct RigidBodyInfo
{
	RigidBodyInfo()
	{
		collider = nullptr;
		mass = 0.0f;
		pos = { 0.0f, 0.0f, 0.0f };
		rot = {	0.0f, 0.0f, 0.0f, 1.0f};
	}
	D3DXVECTOR3 pos;			//���W
	D3DXQUATERNION rot;			//��]
	ICollider* collider;		//�R���C�_�[
	float mass;					//���ʁA�����Ȃ����̂�0.0f�ł���
};

//���̂̃N���X
class RigidBody
{
public:
	//�R���X�g���N�^
	RigidBody()
	{
		m_rigidBody = nullptr;
		m_myMotionState = nullptr;
	}

	//�f�X�g���N�^
	~RigidBody()
	{
		Release();
	}

	/*
	�������֐�
	rbInfo.pos		���W(D3DXVECTOR3)
	rbInfo.rot		��](D3DXQUATERNION)
	rbInfo.collider	�R���C�_�[(ICollider*)
	mass			����(float)
	*/
	void Create(RigidBodyInfo& rbInfo);

	//�����[�X�֐�
	void Release();

	//���̂��擾
	btRigidBody* GetBody()
	{
		return m_rigidBody;
	}

private:
	btDefaultMotionState*	m_myMotionState;		//���[�V�����X�e�C�g
	btRigidBody*			m_rigidBody;			//����
};
