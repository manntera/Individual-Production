#include "stdafx.h"
#include "Goal.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

Goal::Goal()
{
}

Goal::~Goal()
{

}

void Goal::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	//メッシュコライダーからAABBを作成
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 size = (meshCollider.GetAabbMax() - meshCollider.GetAabbMin()) / 2.0f;
	m_boxCollider.Create({ size.x, size.y, size.z });
	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void Goal::Update()
{
	MapChip::Update();
	//プレイヤーがある一定の距離範囲内に入ったらゴール
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		GetGameScene().GameClear();
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}


void Goal::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}