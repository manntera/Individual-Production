#pragma once
//コライダーの基底クラス

class ICollider : Uncopyable
{
public:
	virtual btCollisionShape* GetBody() = 0;
};