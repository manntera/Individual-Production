#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene.h"
#include "../Player/Player.h"

GameCamera::GameCamera() :
	m_camera(),
	m_angleX(0.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_targetManip(5.0f)
{
}

GameCamera::~GameCamera()
{

}

void GameCamera::Init()
{
	//�J�����̏�����
	m_camera.Init();
	m_camera.SetPosition({ 0.0, 40.0f, -40.0f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetNear(3.0f);
	m_camera.SetFar(1000.0f);
	m_camera.Update();
	GetPhysicsWorld().SetCamera(&m_camera);
	//�v���C���[�̃��[���h�s�񂩂�J�����̏������W��ݒ�
	const Player*	player = GetGameScene().GetPlayer();
	D3DXMATRIX mat = player->GetWorldMatrix();
	m_position.x = -mat.m[2][0];
	m_position.y = -mat.m[2][1];
	m_position.z = -mat.m[2][2];
	D3DXVec3Normalize(&m_position, &m_position);
	m_position *= 50.0f;
	D3DXVECTOR3 position = m_position + player->GetPosition();
	m_camera.SetTarget(player->GetPosition());
	m_camera.SetPosition(position);
	D3DXVECTOR3 target = player->GetPosition();
	target.y += m_targetManip;
	m_springCamera.Init(target, position, 120.0f);
	m_springCamera.SetDampingRate(1.3f);
}

bool GameCamera::Start()
{
	return true;
}

void GameCamera::Update()
{
	if (!GetGameScene().IsActive())
	{
		return;
	}
	//m_springCamera.SetTarget(m_camera.GetTarget());
	float angleY = GetPad().GetRightStickX() * GetGameTime().GetDeltaFrameTime() * 30.0f / 180.0f * cPI * 3.0f;
	float angleX = 0.0f;
	float stickY = GetPad().GetRightStickY();
	float limitAngle = 80.0f;
	//�J���������E�܂ōs���ĂȂ�������J������X������ɉ�]������
	if (m_angleX < limitAngle / 180.0f * cPI && 0.0f < stickY || -limitAngle / 180.0f * cPI < m_angleX && stickY < 0.0f)
	{
		angleX = stickY * GetGameTime().GetDeltaFrameTime() * 30.0f / 180.0f * cPI * 3.0f;
		m_angleX += angleX;
	}
	D3DXQUATERNION multi;
	D3DXVECTOR3 axisX = m_springCamera.GetTarget() - m_springCamera.GetTarPosition();
	//�O�����Ə�����̃x�N�g���̊O�ς���艡�����̃x�N�g�������߂�
	D3DXVec3Cross(&axisX, &axisX, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&axisX, &axisX);
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	//Y���̃N�H�[�^�j�I�������J�����̉�]�Ɋ|����
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angleY);
	D3DXQuaternionMultiply(&rotation, &rotation, &multi);
	//�J�����̉����������ɃN�H�[�^�j�I�������J�����̉�]�Ɋ|����
	D3DXQuaternionRotationAxis(&multi, &axisX, angleX);
	D3DXQuaternionMultiply(&rotation, &rotation, &multi);
	//�N�H�[�^�j�I�������]�s������J�����̈ʒu���v���C���[�𒆐S�Ƃ��ĉ�
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationQuaternion(&rotMatrix, &rotation);
	D3DXVECTOR3 position;
	position = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	D3DXVec3TransformCoord(&position, &position, &rotMatrix);
	m_springCamera.SetPosition(position + m_springCamera.GetTarget());
	D3DXVECTOR3 target = GetGameScene().GetPlayer()->GetPosition();
	target.y += m_targetManip;
	//�J�����̍��W�ƒ����_��ݒ肵�čX�V
	position += target;
	m_springCamera.SetTarTarget(target);
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	m_camera.SetTarget(m_springCamera.GetTarget());
	m_camera.SetPosition(m_springCamera.GetPosition());
	m_camera.Update();
}