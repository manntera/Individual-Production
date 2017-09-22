#include "engineStdafx.h"
#include "RigidBody.h"
#include "../Engine.h"
#include "Collider\MeshCollider.h"




void RigidBody::Create(RigidBodyInfo& rbInfo)
{
	Release();
	//btTransform transform;
	//transform.setIdentity();
	//transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	//transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.z));
	m_myMotionState = new btDefaultMotionState();

	btRigidBody::btRigidBodyConstructionInfo btRBInfo(rbInfo.mass, m_myMotionState, rbInfo.collider->GetBody(), btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(btRBInfo);
	GetEngine().GetPhysicsWorld()->AddRigidBody(m_rigidBody);
}

void RigidBody::Release()
{
	if (m_rigidBody != nullptr)
	{
		GetEngine().GetPhysicsWorld()->RemoveRigidBody(m_rigidBody);
		delete m_rigidBody;
		m_rigidBody = nullptr;
	}
	if (m_myMotionState != nullptr)
	{
		delete m_myMotionState;
		m_myMotionState = nullptr;
	}
}