#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene.h"
#include "../Player/Player.h"

GameCamera::GameCamera() :
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_camera(),
	m_angleX(0.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_playerBoneMat(nullptr)
{
}

GameCamera::~GameCamera()
{

}

void GameCamera::Init()
{
	//カメラの初期化
	m_camera.Init();
	m_camera.SetPosition({ 0.0, 40.0f, -40.0f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetNear(3.0f);
	m_camera.SetFar(1000.0f);
	m_camera.Update();
	D3DXQuaternionIdentity(&m_rotation);
	GetPhysicsWorld().SetCamera(&m_camera);
	//プレイヤーのワールド行列からカメラの初期座標を設定
	const Player*	player = GetGameScene().GetPlayer();
	D3DXMATRIX mat = player->GetWorldMatrix();
	m_position.x = -mat.m[2][0];
	m_position.y = -mat.m[2][1];
	m_position.z = -mat.m[2][2];
	D3DXVec3Normalize(&m_position, &m_position);
	m_position *= 50.0f;
}

bool GameCamera::Start()
{

	m_playerBoneMat = GetGameScene().GetPlayer()->FindBoneWorldMatrix("center");
	return true;
}

void GameCamera::Update()
{
	if (!GetGameScene().IsActive())
	{
		return;
	}
	float angleY = GetPad().GetRightStickX() * GetGameTime().GetDeltaFrameTime() * 30.0f / 180.0f * cPI * 3.0f;
	float angleX = 0.0f;
	float stickY = GetPad().GetRightStickY();
	float limitAngle = 80.0f;
	//カメラが限界まで行ってなかったらカメラのX軸周りに回転させる
	if (m_angleX < limitAngle / 180.0f * cPI && 0.0f < stickY || -limitAngle / 180.0f * cPI < m_angleX && stickY < 0.0f)
	{
		angleX = stickY * GetGameTime().GetDeltaFrameTime() * 30.0f / 180.0f * cPI * 3.0f;
		m_angleX += angleX;
	}

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
	D3DXVECTOR3 position = { 0.0f, 0.0f, 0.0f };
	position = m_position;
	D3DXVec3TransformCoord(&position, &position, &rotMatrix);
	D3DXVECTOR3 target;
	target.x = m_playerBoneMat->m[3][0];
	target.y = m_playerBoneMat->m[3][1];
	target.z = m_playerBoneMat->m[3][2];
	//カメラの座標と注視点を設定して更新
	m_camera.SetTarget(target);
	position += target;
	m_camera.SetPosition(position);
	m_camera.Update();
}