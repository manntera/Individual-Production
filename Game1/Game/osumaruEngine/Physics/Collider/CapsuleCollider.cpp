#include "engineStdafx.h"
#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider()
{
	m_shape = nullptr;
}

CapsuleCollider::~CapsuleCollider()
{
	delete m_shape;
}