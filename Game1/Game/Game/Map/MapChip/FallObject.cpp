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
	//	"Assets/particle/WallDust.png",		//テクスチャのファイルパス
	//	0.2f,								//パーティクルの横幅
	//	0.2f,								//パーティクルの縦幅
	//	{ 0.0f, 0.0f, 1.0f, 1.0f },			//テクスチャのuv。xyが左上のuvでzwが右下のuv
	//	{ aabb.x, aabb.y, aabb.z },			//パーティクルの座標のランダム幅
	//	{ 0.0f, -1.0f, 0.0f },				//パーティクルの重力
	//	6.0f,								//パーティクルの寿命
	//	2.0f,								//パーティクルが出るまでのインターバル
	//	0.0f,								//エミッターの寿命
	//	m_position,							//エミッターの座標
	//	13									//1フレームで出るパーティクルの数
	//}
	//, &g_gameScene->GetCamera());
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}



void FallObject::Update()
{
	MapChip::Update();
	//プレイヤーが上に乗ったら落ち始める
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
	//剛体を移動
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