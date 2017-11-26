#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene.h"
#include "../Player/Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::Init()
{
	m_camera.Init();
	m_camera.SetPosition({ 0.0, 40.0f, -40.0f });
	m_camera.SetTarget({0.0f, 0.0f, 0.0f});
	m_camera.SetNear(0.1f);
	m_camera.SetFar(1000.0f);
	D3DXQuaternionIdentity(&m_rotation);
	GetPhysicsWorld().SetCamera(&m_camera);
}

void GameCamera::Update()
{
	if (g_gameScene == nullptr)
	{
		return;
	}
	float angleY = GetPad().GetRightStickX() * 2 / 180.0f * cPI;
	float angleX = GetPad().GetRightStickY() * 2 / 180.0f * cPI;
	D3DXQUATERNION multi;
	D3DXVECTOR3 axisX = m_camera.GetTarget() - m_camera.GetPosition();
	//前方向と上方向のベクトルの外積を取り横方向のベクトルを求める
	D3DXVec3Cross(&axisX, &axisX, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&axisX, &axisX);
	//Y軸のクォータニオンを作りカメラの回転に掛ける
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angleY);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//カメラの横方向を軸にクォータニオンを作りカメラの回転に掛ける
	D3DXQuaternionRotationAxis(&multi, &axisX, angleX);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//クォータニオンから回転行列を作りカメラの位置をプレイヤーを中心として回す
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationQuaternion(&rotMatrix, &m_rotation);
	D3DXVECTOR3 position = {0.0f, 0.0f, 0.0f};
	position.z -= 50.0f;
	D3DXVec3TransformCoord(&position, &position, &rotMatrix);
	Player*	player = g_gameScene->GetPlayer();
	D3DXMATRIX* playerWorldMat = player->FindBoneWorldMatrix("center");
	D3DXVECTOR3 target;
	target.x = playerWorldMat->m[3][0];
	target.y = playerWorldMat->m[3][1];
	target.z = playerWorldMat->m[3][2];
	m_camera.SetTarget(target);
	position += target;
	m_camera.SetPosition(position);
	m_camera.Update();
}