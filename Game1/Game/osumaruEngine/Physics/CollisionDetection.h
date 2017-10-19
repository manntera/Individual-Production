#pragma once
#include "RigidBody.h"
//当たり判定を取るクラス

class CollisionDetection
{
public:

	//コンストラクタ
	CollisionDetection();
	
	//デストラクタ
	~CollisionDetection();

	/*
	初期化関数
	colldier	コライダー
	position	座標
	rotation	回転
	*/
	void Init(ICollider* collider, D3DXVECTOR3 position, D3DXQUATERNION rotation);

	/*
	座標を設定
	*/
	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
		m_rigidBody.GetBody()->getWorldTransform().setOrigin({ position.x, position.y, position.z });
	}

	/*
	回転を設定
	*/
	void SetRotation(D3DXQUATERNION rotation)
	{
		m_rotation = rotation;
		m_rigidBody.GetBody()->getWorldTransform().setRotation({ m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w });
	}

	//実行
	void Execute();

	/*
	当たってるか？
	trueなら当たってる。falseなら当たってない
	*/
	bool IsHit()
	{
		return m_isHit;
	}

	/*
	UserIndexの設定
	userIndex　		設定したいUserIndexの番号
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
	RigidBody		m_rigidBody;		//剛体
	ICollider*		m_pCollider;		//コライダー
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	bool			m_isHit;			//当たってるか？
	D3DXVECTOR3		m_hitCollisionNormal;
};