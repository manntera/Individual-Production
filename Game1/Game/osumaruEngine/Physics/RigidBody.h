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
	float mass;					//質量、動かないものは0.0fでいい
};

//剛体のクラス
class RigidBody
{
public:
	//コンストラクタ
	RigidBody()
	{
		m_rigidBody = nullptr;
		m_myMotionState = nullptr;
	}

	//デストラクタ
	~RigidBody()
	{
		Release();
	}

	/*
	初期化関数
	rbInfo.pos		座標(D3DXVECTOR3)
	rbInfo.rot		回転(D3DXQUATERNION)
	rbInfo.collider	コライダー(ICollider*)
	mass			質量(float)
	*/
	void Create(RigidBodyInfo& rbInfo);

	//リリース関数
	void Release();

	//剛体を取得
	btRigidBody* GetBody()
	{
		return m_rigidBody;
	}

private:
	btDefaultMotionState*	m_myMotionState;		//モーションステイト
	btRigidBody*			m_rigidBody;			//剛体
};
