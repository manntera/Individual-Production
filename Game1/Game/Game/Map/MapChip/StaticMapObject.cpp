#include "stdafx.h"
#include "StaticMapObject.h"

void StaticMapObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからAABBを作成
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 meshAabbMax = m_meshCollider.GetAabbMax();
	m_boxCollider.Create(btVector3(meshAabbMax.x, meshAabbMax.y, meshAabbMax.z));
	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void StaticMapObject::Start()
{
}

void StaticMapObject::Update()
{
	MapChip::Update();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void StaticMapObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_meshCollider.GetBody());
}