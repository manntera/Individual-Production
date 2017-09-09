#pragma once

#include "Collider\CapsuleCollider.h"
#include "RigidBody.h"


//キャラクターコントローラー
//衝突解決と衝突判定をしてくれるクラス。

class CharacterController
{
public:
	//コンストラクタ
	CharacterController();

	//デストラクタ
	~CharacterController();

	/*
	初期化関数
	float		radius		キャラクターの半径　　　
	float		height		キャラクターの高さ　
	D3DXVECTOR3 position	キャラの座標

	コライダーはカプセルコライダーでキャラクターの原点が足元にあることを前提としている。
	*/
	void Init(float radius, float height, const D3DXVECTOR3& position);

	//実行関数
	void Execute();

	//座標を取得。
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}

	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_position = pos;
	}

	//移動速度を設定。
	void SetMoveSpeed(D3DXVECTOR3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
		//上向きに移動速度が与えられていた場合ジャンプするとみなす
		if (m_moveSpeed.y > 0.0f)
		{
			Jump();
		}
	}
	
	//移動速度を取得。
	D3DXVECTOR3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}

	//ジャンプするときに呼ばれる関数。
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}

	//ジャンプしているか？
	bool IsJump() const
	{
		return m_isJump;
	}

	//地面に接地しているか？
	bool IsOnGround()
	{
		return m_isOnGround;
	}

	//コライダーを取得。
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}

	//重力を設定。
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}

	//剛体を削除。
	void RemovedRigidBody();

private:
	D3DXVECTOR3		m_position;			//座標
	D3DXVECTOR3		m_moveSpeed;		//移動速度
	bool			m_isJump;			//ジャンプしているか？
	bool			m_isOnGround;		//地面に設置しているか？
	CapsuleCollider	m_collider;			//コライダー
	float			m_radius;			//半径
	float			m_height;			//高さ
	RigidBody		m_rigidBody;		//剛体
	float			m_gravity;			//重力
};