#include "stdafx.h"
#include "MoveFloor.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

void MoveFloor::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char *modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//���b�V���R���C�_�[����aabb���쐬	
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 boxSize = meshCollider.GetAabbMax();
	m_boxCollider.Create({ boxSize.x, boxSize.y, boxSize.z });

	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//���̂��쐬
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

	//�v���C���[����ɏ������e�q�֌W������
	if (!m_isChild && m_rigidBody.GetBody()->getPlayerCollisionFlg())
	{
		g_gameScene->GetPlayer()->SetParent(this, true);
		m_isChild = true;
	}
	//�v���C���[�����ꂽ�̂Őe�q�֌W���O��
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

	//���̂̃��[���h�s����X�V
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetRotation(m_rotation);
	m_rigidBody.GetBody()->setPlayerCollisionFlg(false);

	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

