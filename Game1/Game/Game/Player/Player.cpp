#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"

void Player::Init()
{
	float ambient = 0.6f;
	float diffuseColor = 0.3f;
	light.SetAmbiemtLight({ ambient, ambient, ambient, 1.0f });
	light.SetDiffuseLightColor(0, { diffuseColor, diffuseColor, diffuseColor, 1.0f });
	light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, 0.707f, 1.0f });
	skinModelData.LoadModelData("Assets/modelData/Unitychan.X", &anim);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	m_modelNormalMap.Load("Assets/modelData/utc_normal.tga");
	m_modelSpecularMap.Load("Assets/modelData/utc_spec.tga");
	skinModel.SetNormalMap(&m_modelNormalMap);
	skinModel.SetSpecularMap(&m_modelSpecularMap);

	D3DXQuaternionIdentity(&rotation);

	trans = { 0.0f, 7.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	anim.SetAnimationEndTime(0, 0.8f);
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	characterController.Init(1.0f, 1.0f, trans);
	characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
}

void Player::Update()
{
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	Camera& camera = g_gameScene->GetCamera()->GetCamera();
	D3DXVECTOR3 front = camera.GetTarget() - camera.GetPosition();
	front.y = 0.0f;
	D3DXVec3Normalize(&front, &front);
	D3DXVECTOR3 side;
	D3DXVec3Cross(&side, &front, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&side, &side);
	float speed = 30.0f;
	moveSpeed += -side * GetPad().GetLeftStickX() * speed;
	moveSpeed += front * GetPad().GetLeftStickY() * speed;
	if (GetPad().IsPressButton(padButtonA))
	{
		moveSpeed.y += 2.0f;
	}
	if (GetPad().IsPressButton(padButtonB))
	{
		anim.PlayAnimation(0);
	}
	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	trans = characterController.GetPosition();
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	anim.Update(1.0f / 60.0f);
}

void Player::Render()
{
	skinModel.Draw(&g_gameScene->GetCamera()->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera()->GetCamera().GetProjectionMatrix());
}
