#include "engineStdafx.h"
#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider()
{
	shape = nullptr;
}

CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}