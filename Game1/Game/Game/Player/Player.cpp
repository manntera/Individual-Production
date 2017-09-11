#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"

void Player::Init()
{
	light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	skinModelData.LoadModelData("../Game/Assets/modelData/snowman1-3-2.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);

	D3DXQuaternionIdentity(&rotation);
	trans = { 0.0f, 7.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	characterController.Init(1.0f, 1.0f, trans);
	characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	//characterController.SetGravity(0.0f);
}

void Player::Update()
{
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	moveSpeed.x = GetPad().GetLeftStickX() * 30.0f;
	moveSpeed.z = GetPad().GetLeftStickY() * 30.0f;
	if (GetPad().IsPressButton(padButtonA))
	{
		moveSpeed.y += 2.0f;
	}
	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	trans = characterController.GetPosition();
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void Player::Render()
{
	skinModel.Draw(&g_gameScene->GetCamera()->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera()->GetCamera().GetProjectionMatrix());
}
