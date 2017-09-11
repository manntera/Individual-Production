#pragma once
#include "ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	//コンストラクタ
	CapsuleCollider();

	//デストラクタ
	~CapsuleCollider();

	/*
	コライダーを作る初期化関数
	radius		コライダーの半径
	height		コライダーの高さ
	*/
	void Create(float radius, float height)
	{
		m_shape = new btCapsuleShape(radius, height);
	}

	//コライダーを取得
	btCollisionShape* GetBody()override
	{
		return m_shape;
	}

private:
	btCapsuleShape*		m_shape;	//コライダー
};