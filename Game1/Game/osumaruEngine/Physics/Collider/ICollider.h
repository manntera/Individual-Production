#pragma once
//コライダーの基底クラス

class ICollider : Uncopyable
{
public:
	virtual const btCollisionShape* GetBody() const = 0;
};