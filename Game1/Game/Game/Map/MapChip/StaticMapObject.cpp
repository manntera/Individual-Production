#include "stdafx.h"
#include "StaticMapObject.h"

void StaticMapObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	//メッシュコライダーからAABBを作成
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 boxSize = meshCollider.GetAabbMax();
	m_boxCollider.Create({boxSize.x, boxSize.y, boxSize.z});

	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;	
	
	//剛体を作成
	rInfo.rot = m_rotation;
	m_rigidBody.Create(rInfo);
}

void StaticMapObject::Start()
{

}
