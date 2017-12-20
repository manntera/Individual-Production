#include "stdafx.h"
#include "FallObject.h"



void FallObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	MeshCollider mesh;
	mesh.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 aabb = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
	m_boxCollider.Create(btVector3(aabb.x, aabb.y, aabb.z));
	RigidBodyInfo rbInfo;
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_boxCollider;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
	m_isActive = false;
}

void FallObject::Update()
{
	MapChip::Update();
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		m_isActive = true;
	}
	if (m_isActive)
	{
		m_position.y -= 0.4f;
	}
	m_rigidBody.SetPosition(m_position);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
}

void FallObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_boxCollider.GetBody());
}