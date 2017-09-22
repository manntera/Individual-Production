#include "stdafx.h"
#include "StaticMapObject.h"

void StaticMapObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)
{
	MapChip::Init(position, rotation, modelName);
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	m_rigidBody.GetBody()->getWorldTransform().setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
}

void StaticMapObject::Start()
{

}
