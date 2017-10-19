#include "engineStdafx.h"
#include "CollisionDetection.h"
#include "../Engine.h"
#include "CollisionAttr.h"

struct ContactSingle : public btCollisionWorld::ContactResultCallback
{
	bool isHit = false;
	D3DXVECTOR3 hitObjectNormal;
	btCollisionObject* me = nullptr;				//自分自身。自分自身との衝突を除外するためのメンバ。

	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)override
	{
		isHit = true;

		D3DXQUATERNION quaternion;
		quaternion = D3DXQUATERNION(colObj1Wrap->getCollisionObject()->getWorldTransform().getRotation());
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &quaternion);
		hitObjectNormal.x = rot.m[1][0];
		hitObjectNormal.y = rot.m[1][1];
		hitObjectNormal.z = rot.m[1][2];
		return 0.0f;
	}
};

CollisionDetection::CollisionDetection()
{
	m_position = { 0.0f, 0.0f, 0.0f };
	D3DXQuaternionIdentity(&m_rotation);
	m_isHit = false;
}

CollisionDetection::~CollisionDetection()
{
	m_rigidBody.Release();
}

void CollisionDetection::Init(ICollider* collider, D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	//剛体を初期化
	RigidBodyInfo rbInfo;
	m_pCollider = collider;
	m_position = position;
	m_rotation = rotation;
	rbInfo.collider = collider;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);
}


void CollisionDetection::Execute()
{
	//collisionWorldと剛体の個別の衝突テスト
	ContactSingle callBack;
	callBack.me = m_rigidBody.GetBody();
	GetEngine().GetPhysicsWorld()->ContactTest(m_rigidBody.GetBody(), callBack);
	m_isHit = callBack.isHit;
	m_hitCollisionNormal = callBack.hitObjectNormal;
}
