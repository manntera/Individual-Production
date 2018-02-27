#include "stdafx.h"
#include "SpringObject.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

SpringObject::SpringObject() :
	m_rigidBody(),
	m_boxCollider(),
	m_anim()
{
	
}

SpringObject::~SpringObject()
{

}

void SpringObject::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName, &m_anim);

	//メッシュコライダーを作成してaabbを求める
	MeshCollider meshCollider;
	meshCollider.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 aabbSize = (meshCollider.GetAabbMax() - meshCollider.GetAabbMin()) / 2;
	m_boxCollider.Create({ aabbSize.x, aabbSize.y, aabbSize.z });

	RigidBodyInfo rInfo;
	rInfo.collider = &m_boxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;

	//剛体を作成
	rInfo.rot = m_rotation;

	m_rigidBody.Create(rInfo);
	m_rigidBody.SetUserIndex(enCollisionAttr_Spring);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	m_anim.SetAnimationLoopFlg(1, false);
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}

void SpringObject::Update()
{
	MapChip::Update();
	//プレイヤーが乗ったので移動速度を与えてプレイヤーを飛ばす
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg())
	{
		D3DXQUATERNION rot = m_rigidBody.GetBody()->getWorldTransform().getRotation();
		D3DXMATRIX rotationMat;
		D3DXMatrixRotationQuaternion(&rotationMat, &rot);
		D3DXVECTOR3 springDirection;
		springDirection.x = rotationMat.m[1][0];
		springDirection.y = rotationMat.m[1][1];
		springDirection.z = rotationMat.m[1][2];
		D3DXVec3Normalize(&springDirection, &springDirection);
		springDirection *= 90.0f;
		m_pPlayer->SetStageGimmickMoveSpeed(springDirection);
		m_anim.PlayAnimation(1);
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/Spring.wav");
		sound->Play(false);
		sound->SetVolume(1.0f);
	}
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	m_anim.Update(GetGameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, m_scale);
}


void SpringObject::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}