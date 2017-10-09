#pragma once
#include "ICollider.h"
//球形状のコライダークラス

class SphereCollider : public ICollider
{
public:

	//コンストラクタ
	SphereCollider();
	
	//デストラクタ
	~SphereCollider();

	/*
	コライダーを作成
	radius		球の半径
	*/
	void Create(float radius);

	//コライダーを取得
	btSphereShape* GetBody()override
	{
		return m_sphereShape;
	}

private:
	btSphereShape* m_sphereShape;	//球のコライダー
};