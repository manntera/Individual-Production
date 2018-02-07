#include "stdafx.h"
#include "RotationObject.h"
#include "../../Player/Player.h"
#include "../../Scene/GameScene.h"

RotationObject::RotationObject() :
	m_rigidBody(),
	m_meshCollider(),
	m_isChild(false),
	m_multi(0.0f, 0.0f, 0.0f, 1.0f)
{

}

RotationObject::~RotationObject()
{

}


void RotationObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//���b�V���R���C�_�[����aabb���쐬	
	m_meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	RigidBodyInfo rInfo;
	rInfo.collider = &m_meshCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//���̂��쐬
	m_rigidBody.Create(rInfo);
	m_rigidBody.SetUserIndex(enCollisionAttr_Rotation);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	//�t���[�����̉�]�ʂ�ݒ�
	D3DXVECTOR3 axis;
	D3DXMATRIX worldMatrix = m_skinModel.GetWorldMatrix();
	axis.x = worldMatrix.m[2][0];
	axis.y = worldMatrix.m[2][1];
	axis.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&axis, &axis);
	D3DXQuaternionRotationAxis(&m_multi, &axis, 1.0f / 180.0f * cPI);
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}

void RotationObject::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	//�q�������Ȃ���ԂŃv���C���[������������e�q�֌W������
	if (!m_isChild && m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		m_pPlayer->SetParent(this, false);
		m_isChild = true;
	}
	//�v���C���[���q���̎��Ƀv���C���[�����ꂽ����e�q�֌W��؂�
	if (m_isChild && !m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		m_pPlayer->SetParent(nullptr, false);
		m_isChild = false;
	}
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &m_multi);

	//���̂��񂵂čX�V
	m_rigidBody.SetRotation(m_rotation);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void RotationObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_meshCollider.GetBody());
}
