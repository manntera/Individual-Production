#pragma once
#include "ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	CapsuleCollider();

	~CapsuleCollider();

	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
	}

	btCollisionShape* GetBody()override
	{
		return shape;
	}

private:
	btCapsuleShape*		shape;
};