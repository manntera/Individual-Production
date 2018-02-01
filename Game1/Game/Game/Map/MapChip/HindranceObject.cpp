#include "stdafx.h"
#include "HindranceObject.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

void HindranceObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char *modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからaabbを作成	
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 boxSize = (meshCollider.GetAabbMax() - meshCollider.GetAabbMin()) / 2.0f;
	m_boxCollider.Create({ boxSize.x, boxSize.y, boxSize.z });
	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);

	m_timerLimit = 60;
	m_timer = GetRandom().GetRandInt() % m_timerLimit;


	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	m_acceleration.x = worldMatrix.m[2][0];
	m_acceleration.y = worldMatrix.m[2][1];
	m_acceleration.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&m_acceleration, &m_acceleration);
	m_acceleration *= 0.15f;
	m_moveSpeed = { 0.0f, 0.0f, 0.0f };
	m_moveSpeed += m_acceleration * (m_timer - m_timerLimit / 2);
	m_isChild = false;
}

void HindranceObject::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	if (m_timerLimit <= m_timer)
	{
		m_acceleration *= -1.0f;
		m_timer = 0;
	}
	m_timer++;
	m_moveSpeed += m_acceleration;
	m_position += m_moveSpeed;
	if (!m_isChild && (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg() || m_rigidBody.GetBody()->getPlayerCollisionWallFlg()))
	{
		m_isChild = g_gameScene->GetPlayer()->SetParent(this, true);
	}
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionGroundFlg() && !m_rigidBody.GetBody()->getPlayerCollisionWallFlg())
	{
		m_isChild = g_gameScene->GetPlayer()->SetParent(nullptr, true);
	}
	D3DXVECTOR3 rigidBodyPos = m_position;
	rigidBodyPos.y -= 3.0f;
	m_rigidBody.SetPosition(rigidBodyPos);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
	m_rigidBody.GetBody()->setPlayerCollisionWallFlg(false);
	m_skinModel.Update(m_position, m_rotation, m_scale);

}

void HindranceObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_boxCollider.GetBody());
}