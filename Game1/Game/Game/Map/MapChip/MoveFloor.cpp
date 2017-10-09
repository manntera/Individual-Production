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

	//剛体を作成
	rInfo.rot = m_rotation;
	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor);
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
	m_timer = 0.0f;
}

void MoveFloor::Update()
{
	MapChip::Update();

	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	m_moveSpeed.x = worldMatrix.m[2][0];
	m_moveSpeed.y = worldMatrix.m[2][1];
	m_moveSpeed.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&m_moveSpeed, &m_moveSpeed);
	m_moveSpeed *= g_moveFloorSpeed;
	m_position += m_moveSpeed;

	if (m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		g_gameScene->GetPlayer()->SetStageGimmickMoveSpeed(m_moveSpeed);
	}

	m_timer += 1.0f / 60.0f;
	if (2.0f < m_timer)
	{
		D3DXQUATERNION multi;
		D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), cPI);
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
		m_timer = 0.0f;
	}

	m_rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	m_rigidBody.GetBody()->getWorldTransform().setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

