#include "stdafx.h"
#include "MoveFloor.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

MoveFloor::MoveFloor() :
	m_timer(0.0f),
	m_moveSpeed(0.0f, 0.0f, 0.0f),
	m_rigidBody(),
	m_boxCollider(),
	m_isChild(false)
{

}

MoveFloor::~MoveFloor()
{

}

void MoveFloor::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char *modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//���b�V���R���C�_�[����aabb���쐬	
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 boxSize = (meshCollider.GetAabbMax() - meshCollider.GetAabbMin()) / 2.0f;
	m_boxCollider.Create({ boxSize.x, boxSize.y, boxSize.z });

	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//���̂��쐬
	m_rigidBody.Create(rInfo);
	m_rigidBody.SetUserIndex(enCollisionAttr_MoveFloor);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	//���[���h�s������ƂɈړ�������ݒ�
	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	m_moveSpeed.x = worldMatrix.m[2][0];
	m_moveSpeed.y = worldMatrix.m[2][1];
	m_moveSpeed.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&m_moveSpeed, &m_moveSpeed);
	m_moveSpeed *= 0.2f;
}

void MoveFloor::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		true;
	}
	m_position += m_moveSpeed;

	//�q�������Ȃ���ԂŃv���C���[������������e�q�֌W������
	if (!m_isChild && (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg() || m_rigidBody.GetBody()->getPlayerCollisionWallFlg()))
	{
		m_isChild = m_pPlayer->SetParent(this, true);
	}
	//�v���C���[���q���̎��Ƀv���C���[�����ꂽ����e�q�֌W��؂�
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionGroundFlg() && !m_rigidBody.GetBody()->getPlayerCollisionWallFlg())
	{
		
		m_isChild = m_pPlayer->SetParent(nullptr, true);
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
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	m_rigidBody.SetPlayerCollisionWallFlg(false);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void MoveFloor::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_boxCollider.GetBody());
}