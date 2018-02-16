#include "stdafx.h"
#include "FallObject.h"
#include "../../Scene/GameScene.h"

FallObject::FallObject() :
	m_isFall(false),
	m_rigidBody(),
	m_boxCollider(),
	m_particle(nullptr),
	m_timer(0.0f)
{
}

FallObject::~FallObject()
{
	ParticleDelete();
}

void FallObject::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	//���̂�������
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
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	//�p�[�e�B�N����������
	//m_particle = New<ParticleEmitter>(CAMERA_PRIORITY);
	//m_particle->Init({
	//	"Assets/particle/WallDust.png",						//�e�N�X�`���̃t�@�C���p�X
	//	0.4f,												//�p�[�e�B�N���̉���
	//	0.4f,												//�p�[�e�B�N���̏c��
	//	{ 0.0f, 0.0f, 1.0f, 1.0f },							//�e�N�X�`����uv�Bxy�������uv��zw���E����uv
	//	{ aabb.x, 3.0f, aabb.z },					//�p�[�e�B�N���̍��W�̃����_����
	//	{ 0.0f, -0.5f, 0.0f },								//�p�[�e�B�N���̏d��
	//	1.3f,												//�p�[�e�B�N���̎���
	//	1.0f,												//�p�[�e�B�N�����o��܂ł̃C���^�[�o��
	//	0.0f,												//�G�~�b�^�[�̎���
	//	{ m_position.x, m_position.y - 11.0f, m_position.z },//�G�~�b�^�[�̍��W
	//	2,													//1�t���[���ŏo��p�[�e�B�N���̐�
	//	true												//�ŏ��Ƀp�[�e�B�N�����G�~�b�g���鎞�������Ԃ������_���ɂ��邩
	//}
	//, &GetGameScene().GetCamera());
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}



void FallObject::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	//�v���C���[����ɏ�����痎���n�߂�
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		m_isFall = true;
		ParticleDelete();
	}
	if (m_isFall)
	{
		m_position.y -= 0.2f;
		m_timer += GetGameTime().GetDeltaFrameTime();
		//�����n�߂Ă�����x���Ԃ����Ə�����
		if (3.5f < m_timer)
		{
			MapChipDelete();
		}
	}
	//���̂��ړ�
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	m_skinModel.Update(m_position, m_rotation, m_scale);
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