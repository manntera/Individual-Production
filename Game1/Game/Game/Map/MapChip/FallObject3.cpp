#include "stdafx.h"
#include "FallObject3.h"
#include "../../Scene/GameScene.h"

FallObject3::FallObject3() :
	m_isFall(false),
	m_rigidBody(),
	m_boxCollider(),
	m_timer(0.0f),
	m_animationTimer(0.0f),
	m_animationMove(0.0f, 0.0f, 0.0f),
	m_pSound(nullptr),
	m_soundVolume(1.0f),
	m_revivalTime(0.0f),
	m_isDead(false)
{
}

FallObject3::~FallObject3()
{
	SoundDelete();
}

void FallObject3::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	//剛体を初期化
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
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
	m_animationMove.x = (float)GetRandom().GetRandDouble();
	m_animationMove.y = (float)GetRandom().GetRandDouble();
	m_animationMove.z = (float)GetRandom().GetRandDouble();
	D3DXVec3Normalize(&m_animationMove, &m_animationMove);
	m_animationMove *= 0.18f;
	m_initPos = m_position;
}



void FallObject3::Update()
{
	if (m_isDead)
	{
		m_revivalTime += GetGameTime().GetDeltaFrameTime();
		if (8.0f < m_revivalTime)
		{
			m_isDead = false;
			Reset();
		}
		return;
	}
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	//プレイヤーが上に乗ったら落ち始める
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg() && !m_isFall)
	{
		m_isFall = true;
		m_pSound = New<SoundSource>(0);
		m_pSound->Init("Assets/sound/seismic.wav");
		m_pSound->SetVolume(m_soundVolume);
		m_pSound->Play(true);
	}
	if (m_isFall)
	{
		const float animationLimit = 1.2f;
		if (m_animationTimer < animationLimit)
		{
			static int frameNum = 0;
			m_position += m_animationMove;
			if (frameNum % 2 == 0)
			{
				m_animationMove *= -1.0f;
			}
			m_animationTimer += GetGameTime().GetDeltaFrameTime();
			frameNum++;
		}
		else
		{
			m_position.y -= 0.2f;
			m_timer += GetGameTime().GetDeltaFrameTime();
			//落ち始めてある程度時間がたつと消える
			if (3.5f < m_timer)
			{
				m_isDead = true;
				m_rigidBody.PhysicsWorldRemoveRigidBody();
			}
			if (0.0f < m_soundVolume)
			{
				m_pSound->SetVolume(m_soundVolume);
				m_soundVolume -= GetGameTime().GetDeltaFrameTime() * 0.5f;
			}
			else
			{
				SoundDelete();
			}
		}
	}
	//剛体を移動
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void FallObject3::Reset()
{
	m_isFall = false;
	m_timer = 0.0f;
	m_animationTimer = 0.0f;
	m_revivalTime = 0.0f;
	m_isDead = false;
	SoundDelete();
	m_position = m_initPos;
	m_soundVolume = 1.0f;
	m_rigidBody.PhysicsWorldAddRigidBody();
	m_rigidBody.SetPosition(m_position);
}


void FallObject3::SoundDelete()
{
	if (m_pSound != nullptr)
	{
		Delete(m_pSound);
		m_pSound = nullptr;
	}
}


void FallObject3::Draw()
{
	if (m_isDead)
	{
		return;
	}
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}