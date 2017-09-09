#pragma once
//コライダーの基底クラス

class ICollider
{
public:
	virtual btCollisionShape* GetBody() = 0;
};