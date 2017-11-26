#include "stdafx.h"
#include "MoveFloor.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

void MoveFloor::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char *modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからaabbを作成	
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 boxSize = meshCollider.GetAabbMax();
	m_boxCollider.Create({ boxSize.x, boxSize.y, boxSize.z });

	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor);
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
	
	m_timer = 0.0f;
	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	m_moveSpeed.x = worldMatrix.m[2][0];
	m_moveSpeed.y = worldMatrix.m[2][1];
	m_moveSpeed.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&m_moveSpeed, &m_moveSpeed);
	m_moveSpeed *= 0.2f;
	m_isChild = false;
}

void MoveFloor::Update()
{
	MapChip::Update();

	m_position += m_moveSpeed;

	//プレイヤーが上に乗ったら親子関係をつける
	if (!m_isChild && m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		g_gameScene->GetPlayer()->SetParent(this, true);
		m_isChild = true;
	}
	//プレイヤーが離れたので親子関係を外す
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		g_gameScene->GetPlayer()->SetParent(nullptr, true);
		m_isChild = false;
	}
	m_timer += 1.0f / 60.0f;
	if (5.0f < m_timer)
	{
		m_moveSpeed *= -1.0f;
		m_timer = 0.0f;
	}

	//剛体のワールド行列を更新
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetRotation(m_rotation);
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);

	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

