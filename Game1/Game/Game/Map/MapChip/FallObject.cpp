#include "stdafx.h"
#include "FallObject.h"
#include "../../Scene/GameScene.h"

FallObject::FallObject() :
	m_isFall(false),
	m_rigidBody(),
	m_boxCollider(),
	m_timer(0.0f)
{
}

FallObject::~FallObject()
{
}

void FallObject::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	//剛体を初期化
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
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}



void FallObject::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	//プレイヤーが上に乗ったら落ち始める
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		m_isFall = true;
	}
	if (m_isFall)
	{
		m_position.y -= 0.2f;
		m_timer += GetGameTime().GetDeltaFrameTime();
		//落ち始めてある程度時間がたつと消える
		if (3.5f < m_timer)
		{
			MapChipDelete();
		}
	}
	//剛体を移動
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}


void FallObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}