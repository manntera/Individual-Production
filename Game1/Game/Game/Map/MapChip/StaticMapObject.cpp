#include "stdafx.h"
#include "StaticMapObject.h"

StaticMapObject::StaticMapObject() :
	m_rigidBody(),
	m_meshCollider()
{

}

StaticMapObject::~StaticMapObject()
{

}

void StaticMapObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからAABBを作成
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}


void StaticMapObject::Update()
{
	MapChip::Update();
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void StaticMapObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_meshCollider.GetBody());
}