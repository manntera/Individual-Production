#include "engineStdafx.h"
#include "SphereCollider.h"


SphereCollider::SphereCollider() :
	m_sphereShape(nullptr)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Create(float radius)
{
	m_sphereShape.reset(new btSphereShape(radius));
}