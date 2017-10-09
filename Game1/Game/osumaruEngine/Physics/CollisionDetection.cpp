#include "engineStdafx.h"
#include "CollisionDetection.h"
#include "../Engine.h"
#include "CollisionAttr.h"

struct ContactSingle : public btCollisionWorld::ContactResultCallback
{
	bool m_isHit = false;
	btCollisionObject* me = nullptr;				//自分自身。自分自身との衝突を除外するためのメンバ。

	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)override
	{
		m_isHit = true;
		//for (int i = 0; i < index1; i++)
		//{
		//	if (colObj1Wrap[i].getCollisionObject()->getUserIndex() != enCollisionAttr_Character)
		//	{
		//		m_isHit = true;
		//		return 0.0f;
		//	}
		//}
		//for (int i = 0; i < index0; i++)
		//{
		//	if (colObj0Wrap[i].getCollisionObject()->getUserIndex() != enCollisionAttr_Character)
		//	{
		//		m_isHit = true;
		//		return 0.0f;
		//	}
		//}
		return 0.0f;
	}
};

CollisionDetection::CollisionDetection()
{
	m_position = { 0.0f, 0.0f, 0.0f };
	D3DXQuaternionIdentity(&m_rotation);
	m_isHit = true;
}

CollisionDetection::~CollisionDetection()
{

}

void CollisionDetection::Init(ICollider* collider, D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	RigidBodyInfo rbInfo;
	m_pCollider = collider;
	m_position = position;
	m_rotation = rotation;
	rbInfo.collider = collider;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
}


void CollisionDetection::Execute()
{
	ContactSingle callBack;
	callBack.me = m_rigidBody.GetBody();
	GetEngine().GetPhysicsWorld()->ContactTest(m_rigidBody.GetBody(), callBack);
	m_isHit = callBack.m_isHit;
}

void CollisionDetection::Draw()
{
	//GetEngine().GetPhysicsWorld()->DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}
