#include "stdafx.h"
#include "HindranceObject.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

void HindranceObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char *modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからaabbを作成	
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 boxSize = m_meshCollider.GetAabbMax();
	m_boxCollider.Create({ boxSize.x, boxSize.y, boxSize.z });
	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);

	m_timerLimit = 3.0f;
	m_timer = m_timerLimit * 0.5f;

	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	m_acceleration.x = worldMatrix.m[2][0];
	m_acceleration.y = worldMatrix.m[2][1];
	m_acceleration.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&m_acceleration, &m_acceleration);
	m_acceleration *= 0.01f;
	m_moveSpeed = { 0.0f, 0.0f, 0.0f };
	m_isChild = false;
}

void HindranceObject::Update()
{
	MapChip::Update();
	m_moveSpeed += m_acceleration;
	m_position += m_moveSpeed;

	if (!m_isChild && m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		g_gameScene->GetPlayer()->SetParent(this, true);
		m_isChild = true;
	}
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		g_gameScene->GetPlayer()->SetParent(nullptr, true);
		m_isChild = false;
	}
	m_timer += 1.0f / 60.0f;
	if (m_timerLimit < m_timer)
	{
		m_acceleration *= -1.0f;
		m_timer = 0.0f;
	}

	m_rigidBody.SetPosition(m_position);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void HindranceObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_meshCollider.GetBody());
}