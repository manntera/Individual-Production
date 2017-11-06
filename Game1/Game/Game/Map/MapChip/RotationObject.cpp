#include "stdafx.h"
#include "RotationObject.h"
#include "../../Player/Player.h"
#include "../../Scene/GameScene.h"


void RotationObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
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

	D3DXVECTOR3 axis;
	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	axis.x = worldMatrix.m[2][0];
	axis.y = worldMatrix.m[2][1];
	axis.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&axis, &axis);
	D3DXQuaternionRotationAxis(&m_multi, &axis, 1.0f / 180.0f * cPI);
	m_isChild = false;
}

void RotationObject::Update()
{
	MapChip::Update();
	
	if (!m_isChild && m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		g_gameScene->GetPlayer()->SetParent(this, false);
		m_isChild = true;
	}
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		g_gameScene->GetPlayer()->SetParent(nullptr, false);
		m_isChild = false;
	}
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &m_multi);

	m_rigidBody.GetBody()->getWorldTransform().setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}
