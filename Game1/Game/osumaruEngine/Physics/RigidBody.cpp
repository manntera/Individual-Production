#include "engineStdafx.h"
#include "RigidBody.h"
#include "../Engine.h"
#include "Collider\MeshCollider.h"




void RigidBody::Create(RigidBodyInfo& rbInfo)
{
	Release();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.z));
	myMotionState = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo btRBInfo(rbInfo.mass, myMotionState, rbInfo.collider->GetBody(), btVector3(0, 0, 0));
	rigidBody = new btRigidBody(btRBInfo);
	GetEngine().GetPhysicsWorld()->AddRigidBody(rigidBody);
}

void RigidBody::Release()
{
	if (rigidBody != nullptr)
	{
		GetEngine().GetPhysicsWorld()->RemoveRigidBody(rigidBody);
		delete rigidBody;
		rigidBody = nullptr;
	}
	if (myMotionState != nullptr)
	{
		delete myMotionState;
		myMotionState = nullptr;
	}
}