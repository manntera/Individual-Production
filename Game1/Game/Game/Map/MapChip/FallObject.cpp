#include "stdafx.h"
#include "FallObject.h"
#include "../../Scene/GameScene.h"

FallObject::FallObject()
{
	m_particle = nullptr;
	m_timer = 0.0f;
}

FallObject::~FallObject()
{
	ParticleDelete();
}

void FallObject::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	MeshCollider mesh;
	mesh.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 aabb = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
	m_boxCollider.Create(btVector3(aabb.x, aabb.y, aabb.z));
	RigidBodyInfo rbInfo;
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_boxCollider;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
	m_isActive = false;
	//m_particle = New<ParticleEmitter>(cameraPriority);
	//m_particle->Init({
	//	"Assets/particle/WallDust.png",		//�e�N�X�`���̃t�@�C���p�X
	//	0.2f,								//�p�[�e�B�N���̉���
	//	0.2f,								//�p�[�e�B�N���̏c��
	//	{ 0.0f, 0.0f, 1.0f, 1.0f },			//�e�N�X�`����uv�Bxy�������uv��zw���E����uv
	//	{ aabb.x, aabb.y, aabb.z },			//�p�[�e�B�N���̍��W�̃����_����
	//	{ 0.0f, -1.0f, 0.0f },				//�p�[�e�B�N���̏d��
	//	6.0f,								//�p�[�e�B�N���̎���
	//	2.0f,								//�p�[�e�B�N�����o��܂ł̃C���^�[�o��
	//	0.0f,								//�G�~�b�^�[�̎���
	//	m_position,							//�G�~�b�^�[�̍��W
	//	13									//1�t���[���ŏo��p�[�e�B�N���̐�
	//}
	//, &g_gameScene->GetCamera());
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}



void FallObject::Update()
{
	MapChip::Update();
	//�v���C���[����ɏ�����痎���n�߂�
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		m_isActive = true;
		ParticleDelete();
	}
	if (m_isActive)
	{
		m_position.y -= 0.4f;
		m_timer += GetGameTime().GetDeltaFrameTime();
		if (3.0f < m_timer)
		{
			MapChipDelete();
		}
	}
	//���̂��ړ�
	m_rigidBody.SetPosition(m_position);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	m_rigidBody.GetBody()->setPlayerCollisionGroundFlg(false);
}

void FallObject::ParticleDelete()
{
	if (m_particle != nullptr)
	{
		Delete(m_particle);
		m_particle = nullptr;
	}
}


void FallObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_boxCollider.GetBody());
}