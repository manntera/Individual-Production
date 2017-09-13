#include "engineStdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	m_boxShape = nullptr;
}

BoxCollider::~BoxCollider()
{
	delete m_boxShape;
}

