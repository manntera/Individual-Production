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
	m_camera.SetNear(3.0f);
	m_camera.SetFar(1000.0f);
	m_camera.Update();
	D3DXQuaternionIdentity(&m_rotation);
	GetPhysicsWorld().SetCamera(&m_camera);
	m_angleX = 0.0f;
}

void GameCamera::Update()
{
	if (g_gameScene == nullptr)
	{
		return;
	}
	float angleY = GetPad().GetRightStickX() * GetGameTime().GetDeltaFrameTime() * 30.0f / 180.0f * cPI * 3.0f;
	float angleX = 0.0f;
	float stickY = GetPad().GetRightStickY();
	float limitAngle = 80.0f;
	if (m_angleX < limitAngle / 180.0f * cPI && 0.0f < stickY || -limitAngle / 180.0f * cPI < m_angleX && stickY < 0.0f)
	{
		angleX = stickY * GetGameTime().GetDeltaFrameTime() * 30.0f / 180.0f * cPI * 3.0f;
		m_angleX += angleX;
	}
	
	D3DXQUATERNION multi;
	D3DXVECTOR3 axisX = m_camera.GetTarget() - m_camera.GetPosition();
	//�O�����Ə�����̃x�N�g���̊O�ς���艡�����̃x�N�g�������߂�
	D3DXVec3Cross(&axisX, &axisX, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&axisX, &axisX);
	//Y���̃N�H�[�^�j�I�������J�����̉�]�Ɋ|����
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angleY);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//�J�����̉����������ɃN�H�[�^�j�I�������J�����̉�]�Ɋ|����
	D3DXQuaternionRotationAxis(&multi, &axisX, angleX);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//�N�H�[�^�j�I�������]�s������J�����̈ʒu���v���C���[�𒆐S�Ƃ��ĉ�
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