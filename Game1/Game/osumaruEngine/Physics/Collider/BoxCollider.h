#pragma once
#include "ICollider.h"
//箱のコライダー

class BoxCollider : public ICollider
{
public:
	//コンストラクタ
	BoxCollider();

	//デストラクタ
	~BoxCollider();
	
	/*
	コライダーの初期化
	box		ボックスのサイズ
	*/
	void Create(btVector3 box)
	{
		m_boxShape = new btBoxShape(box);
	}

	//コライダーを取得
	btCollisionShape* GetBody()override
	{
		return m_boxShape;
	}
private:
	btBoxShape*		m_boxShape;//コライダー
};
