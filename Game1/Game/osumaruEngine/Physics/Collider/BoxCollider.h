#pragma once
#include "ICollider.h"

class BoxCollider : public ICollider
{
public:
	BoxCollider();

	~BoxCollider();
	
	void Create(btVector3 box)
	{
		m_boxShape = new btBoxShape(box);
	}

	btCollisionShape* GetBody()override
	{
		return m_boxShape;
	}
private:
	btBoxShape*		m_boxShape;
};
