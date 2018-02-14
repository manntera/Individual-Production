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
	void Init(const ICollider* collider, const D3DXVECTOR3& position, const D3DXQUATERNION& rotation);

	/*
	座標を設定
	*/
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
		m_rigidBody.SetPosition(position);
	}

	/*
	回転を設定
	*/
	void SetRotation(const D3DXQUATERNION& rotation)
	{
		m_rotation = rotation;
		m_rigidBody.SetRotation(m_rotation);
	}

	//実行
	void Execute();

	/*
	当たってるか？
	trueなら当たってる。falseなら当たってない
	*/
	bool IsHit() const
	{
		return m_isHit;
	}

	/*
	UserIndexの設定
	userIndex　		設定したいUserIndexの番号
	*/
	void SetUserIndex(int userIndex)
	{
		m_rigidBody.SetUserIndex(userIndex);
	}

	//当たったオブジェクトの法線を取得
	const D3DXVECTOR3& GetCollisionNormal() const
	{
		return m_hitCollisionNormal;
	}

	//回転を取得
	const D3DXQUATERNION& GetRotation() const
	{
		return m_rotation;
	}

	//座標を取得
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}

	//ヒットしたコリジョンの属性を取得
	int GetHitCollisionType() const
	{
		return m_collisionType;
	}

	//このコリジョンの属性を設定
	void SetJudgmentType(int judgmentType)
	{
		m_judgmentType = judgmentType;
	}
private:
	RigidBody				m_rigidBody;			//剛体
	const ICollider*		m_pCollider;			//コライダー
	D3DXVECTOR3				m_position;				//座標
	D3DXQUATERNION			m_rotation;				//回転
	bool					m_isHit;				//当たってるか？
	D3DXVECTOR3				m_hitCollisionNormal;	//テスト用
	int						m_collisionType;		//ヒットしたｺﾘｼﾞｮﾝの属性
	int						m_judgmentType;			//このコリジョンの属性
};