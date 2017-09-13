#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()

{

}

void GameCamera::Init()
{
	camera.Init();
	camera.SetPosition({ 0.0, 40.0f, -40.0f });
	camera.SetTarget({0.0f, 0.0f, 0.0f});
	D3DXQuaternionIdentity(&rotation);
}

void GameCamera::Update()
{
	float angleY = GetPad().GetRightStickX() * 2 / 180.0f * cPI;
	float angleX = GetPad().GetRightStickY() * 2 / 180.0f * cPI;
	D3DXQUATERNION multi;
	D3DXVECTOR3 axisX = camera.GetTarget() - camera.GetPosition();
	D3DXVec3Cross(&axisX, &axisX, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&axisX, &axisX);
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angleY);
	D3DXQuaternionMultiply(&rotation, &rotation, &multi);
	D3DXQuaternionRotationAxis(&multi, &axisX, angleX);
	D3DXQuaternionMultiply(&rotation, &rotation, &multi);
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationQuaternion(&rotMatrix, &rotation);
	Player*	player = g_gameScene->GetPlayer();
	D3DXVECTOR3 target = player->GetPosition();
	camera.SetTarget(target);
	D3DXVECTOR3 position = {0.0f, 0.0f, 0.0f};
	position.z -= 25.0f;
	D3DXVec3TransformCoord(&position, &position, &rotMatrix);
	position += target;
	camera.SetPosition(position);
	camera.Update();
}