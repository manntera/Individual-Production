#include "stdafx.h"
#include "SpringObject.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

void SpringObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName, &m_anim);

	//メッシュコライダーを作成
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
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Spring);
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
	m_anim.SetAnimationLoopFlg(1, false);
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
		m_anim.PlayAnimation(1);
	}
	if (GetPad().IsTriggerButton(enButtonY))
	{
		m_anim.PlayAnimation(1);
	}
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
	m_anim.Update(1.0f / 60.0f);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}
