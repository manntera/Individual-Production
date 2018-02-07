#include "stdafx.h"
#include "StaticMapObject.h"

StaticMapObject::StaticMapObject() :
	m_rigidBody(),
	m_boxCollider()
{

}

StaticMapObject::~StaticMapObject()
{

}

void StaticMapObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからAABBを作成
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 size = (meshCollider.GetAabbMax() - meshCollider.GetAabbMin()) / 2.0f;
	m_boxCollider.Create({size.x, size.y, size.z});
	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}


void StaticMapObject::Update()
{
	MapChip::Update();
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void StaticMapObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_boxCollider.GetBody());
}