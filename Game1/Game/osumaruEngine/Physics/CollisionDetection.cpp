#include "engineStdafx.h"
#include "CollisionDetection.h"
#include "../Engine.h"
#include "CollisionAttr.h"

struct ContactSingle : public btCollisionWorld::ContactResultCallback
{
	bool isHit = false;
	D3DXVECTOR3 hitObjectNormal;
	const btCollisionObject* me = nullptr;				//自分自身。自分自身との衝突を除外するためのメンバ。
	int collisionType = enCollisionAttr_Unknown;
	int judgmentType = enJudgment_Wall;

	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)override
	{
		isHit = true;

		D3DXQUATERNION quaternion;
		quaternion = D3DXQUATERNION(colObj1Wrap->getCollisionObject()->getWorldTransform().getRotation());
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &quaternion);
		hitObjectNormal.x = cp.m_normalWorldOnB.x();
		hitObjectNormal.y = cp.m_normalWorldOnB.y();
		hitObjectNormal.z = cp.m_normalWorldOnB.z();
		collisionType = colObj1Wrap->getCollisionObject()->getUserIndex();
		if (collisionType != enCollisionAttr_Character)
		{
			switch (judgmentType)
			{
			case enJudgment_Ground:
				const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject())->setPlayerCollisionGroundFlg(true);
				break;
			case enJudgment_Wall:
				const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject())->setPlayerCollisionWallFlg(true);
				break;
			default:
				break;
			}
		}
		return 0.0f;
	}
};

CollisionDetection::CollisionDetection() :
	m_rigidBody(),
	m_pCollider(nullptr),
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_isHit(false),
	m_hitCollisionNormal(0.0f, 0.0f, 0.0f),
	m_collisionType(0),
	m_judgmentType(0)
{
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
	m_rigidBody.SetActivationState(DISABLE_DEACTIVATION);
	m_rigidBody.SetUserIndex(enCollisionAttr_Detection);
}

void CollisionDetection::Execute()
{
	//collisionWorldと剛体の個別の衝突テスト
	ContactSingle callBack;
	callBack.me = m_rigidBody.GetBody();
	callBack.judgmentType = m_judgmentType;
	GetPhysicsWorld().ContactTest(m_rigidBody.GetBody(), callBack);
	m_isHit = callBack.isHit;
	m_collisionType = callBack.collisionType;
	m_hitCollisionNormal = callBack.hitObjectNormal;
}
