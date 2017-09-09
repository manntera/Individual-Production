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
	float mass;					//����
};

//���̂̃N���X
class RigidBody
{
public:

	RigidBody()
	{
		rigidBody = nullptr;
		myMotionState = nullptr;
	}

	~RigidBody()
	{
		Release();
	}

	void Create(RigidBodyInfo& rbInfo);

	void Release();

	btRigidBody* GetBody()
	{
		return rigidBody;
	}

private:
	btDefaultMotionState*	myMotionState;
	btRigidBody*			rigidBody;
};
