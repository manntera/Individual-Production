#include "stdafx.h"
#include "SpringObject.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

void SpringObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーを作成
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);

	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;

	//剛体を作成
	rInfo.rot = m_rotation;

	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	m_rigidBody.GetBody()->getWorldTransform().setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Spring);
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
}

void SpringObject::Update()
{
	MapChip::Update();
	if (m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		D3DXQUATERNION rot = m_rigidBody.GetBody()->getWorldTransform().getRotation();
		D3DXMATRIX rotationMat;
		D3DXMatrixRotationQuaternion(&rotationMat, &rot);
		D3DXVECTOR3 springDirection;
		springDirection.x = rotationMat.m[1][0];
		springDirection.y = rotationMat.m[1][1];
		springDirection.z = rotationMat.m[1][2];
		D3DXVec3Normalize(&springDirection, &springDirection);
		springDirection *= 2.0f;
		g_gameScene->GetPlayer()->SetStageGimmickMoveSpeed(springDirection);
	}
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
}
