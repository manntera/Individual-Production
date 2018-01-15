#include "stdafx.h"
#include "RotationObject.h"
#include "../../Player/Player.h"
#include "../../Scene/GameScene.h"


void RotationObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからaabbを作成	
	//MeshCollider meshCollider;
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	//D3DXVECTOR3 boxSize = meshCollider.GetAabbMax();
	//m_boxCollider.Create({ boxSize.x, boxSize.y, boxSize.z });

	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.Create(rInfo);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Rotation);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);

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
	
	//プレイヤーが上に乗ったので親子関係をつける
	if (!m_isChild && m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		g_gameScene->GetPlayer()->SetParent(this, false);
		m_isChild = true;
	}
	//プレイヤーが離れたので親子関係を外す
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		g_gameScene->GetPlayer()->SetParent(nullptr, false);
		m_isChild = false;
	}
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &m_multi);

	m_rigidBody.SetRotation(m_rotation);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void RotationObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_meshCollider.GetBody());
}
