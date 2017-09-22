#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	float ambient = 0.6f;
	float diffuseColor = 0.3f;
	m_light.SetAmbiemtLight({ ambient, ambient, ambient, 1.0f });
	m_light.SetDiffuseLightColor(0, { diffuseColor, diffuseColor, diffuseColor, 1.0f });
	m_light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, 0.707f, 1.0f });

	m_rotation = rotation;
	m_position = position;
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_characterController.Init(1.0f, 1.0f, m_position);
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_characterController.SetGravity(-20.0f);
	m_skinModel.SetShadowCasterFlg(true);
	m_skinModel.SetShadowReceiverFlg(true);
}

void Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/Unitychan.X", &m_anim);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&m_light);
	m_modelNormalMap.Load("Assets/modelData/utc_normal.tga");
	m_modelSpecularMap.Load("Assets/modelData/utc_spec.tga");
	m_skinModel.SetNormalMap(&m_modelNormalMap);
	m_skinModel.SetSpecularMap(&m_modelSpecularMap, &g_gameScene->GetCamera());
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_anim.SetAnimationEndTime(0, 0.8f);
}

void Player::Update()
{
	D3DXVECTOR3 moveSpeed = m_characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	Camera& camera = g_gameScene->GetCamera();
	D3DXVECTOR3 front = camera.GetTarget() - camera.GetPosition();
	front.y = 0.0f;
	D3DXVec3Normalize(&front, &front);
	D3DXVECTOR3 side;
	D3DXVec3Cross(&side, &front, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&side, &side);
	float speed = 30.0f;
	moveSpeed += -side * GetPad().GetLeftStickX() * speed;
	moveSpeed += front * GetPad().GetLeftStickY() * speed;
	if (GetPad().IsTriggerButton(padButtonA))
	{
		moveSpeed.y += 15.0f;
	}
	
	if (GetPad().IsPressButton(padButtonB))
	{
		m_anim.PlayAnimation(0);
	}

	D3DXVECTOR3 moveDir = moveSpeed;
	moveDir.y = 0.0f;
	if (0.0f < D3DXVec3Length(&moveDir))
	{
		D3DXMATRIX worldMat = m_skinModel.GetWorldMatrix();
		D3DXVECTOR3 playerFront;
		playerFront.x = 0.0f;
		playerFront.y = 0.0f;
		playerFront.z = 1.0f;
		D3DXVec3Normalize(&moveDir, &moveDir);
		D3DXVec3Normalize(&playerFront, &playerFront);
		float rad = acos(D3DXVec3Dot(&playerFront, &moveDir));
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &playerFront, &moveDir);
		if (cross.y < 0.0f)
		{
			rad = -rad;
		}
		D3DXQUATERNION multi;
		D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
		//D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	}


	m_characterController.SetMoveSpeed(moveSpeed);
	m_characterController.Execute();
	m_position = m_characterController.GetPosition();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_anim.Update(1.0f / 60.0f);
}

void Player::Render()
{
	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());
}
