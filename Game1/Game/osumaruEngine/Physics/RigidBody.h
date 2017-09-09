#pragma once
class ICollider;

//剛体情報
struct RigidBodyInfo
{
	RigidBodyInfo()
	{
		collider = nullptr;
		mass = 0.0f;
		pos = { 0.0f, 0.0f, 0.0f };
		rot = {	0.0f, 0.0f, 0.0f, 1.0f};
	}
	D3DXVECTOR3 pos;			//座標
	D3DXQUATERNION rot;			//回転
	ICollider* collider;		//コライダー
	float mass;					//質量
};

//剛体のクラス
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
