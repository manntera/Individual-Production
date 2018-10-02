#include "stdafx.h"
#include "HindranceObject.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

HindranceObject::HindranceObject() :
	m_moveSpeed(0.0f, 0.0f, 0.0f),
	m_acceleration(0.0f, 0.0f, 0.0f),
	m_rigidBody(),
	m_boxCollider(),
	m_isChild(false),
	m_timerLimit(60),
	m_timer(GetRandom().GetRandInt() % m_timerLimit)
{

}

HindranceObject::~HindranceObject()
{

}

void HindranceObject::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char *modelName, Animation* anim)
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

	//���f���̕����ňړ����x�Ɖ����x��������
	const D3DXMATRIX& worldMatrix = m_skinModel.GetWorldMatrix();
	m_acceleration.x = worldMatrix.m[2][0];
	m_acceleration.y = worldMatrix.m[2][1];
	m_acceleration.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&m_acceleration, &m_acceleration);
	m_acceleration *= 0.15f;
	m_moveSpeed += m_acceleration * (m_timer - m_timerLimit / 2);
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}

void HindranceObject::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		//�A�N�e�B�u�łȂ����
		m_rigidBody.SetPosition(m_position);
		return;
	}
	//��莞�Ԃňړ������𔽓]����
	if (m_timerLimit <= m_timer)
	{
		m_acceleration *= -1.0f;
		m_timer = 0;
	}
	m_timer++;
	m_moveSpeed += m_acceleration;
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
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	m_rigidBody.SetPlayerCollisionWallFlg(false);
	m_skinModel.Update(m_position, m_rotation, m_scale);

}

void HindranceObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}