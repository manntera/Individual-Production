#include "engineStdafx.h"
#include "SphereCollider.h"


SphereCollider::SphereCollider()
{
	m_sphereShape = nullptr;
}

SphereCollider::~SphereCollider()
{
	delete m_sphereShape;
}

void SphereCollider::Create(float radius)
{
	m_sphereShape = new btSphereShape(radius);
}