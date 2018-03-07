#include "stdafx.h"
#include "Sky.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"

Sky::Sky() :
	m_skinModel(),
	m_skinModelData(),
	m_position(0.0f, 0.0, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_light(),
	m_stageNum(0)
{

}

Sky::~Sky()
{

}

void Sky::Init(int stageNum)
{
	m_stageNum = stageNum;
}

bool Sky::Start()
{
	char* filePath;
	m_position = { 0.0f, -60.0f, 0.0f };
	switch (m_stageNum)
	{
	case 0:
		filePath = "Assets/modelData/SkyBox3.X";
		break;
	case 1:
		filePath = "Assets/modelData/SkyBox3.X";
		break;
	case 2:
		filePath = "Assets/modelData/SkyBox3.X";
		m_position.y += 50.0f;
		break;
	case 3:
		filePath = "Assets/modelData/EveningSkyBox3.X";
		m_position.y += 50.0f;
		break;
	case 4:
		filePath = "Assets/modelData/NightSkyBox3.X";
		break;
	}
	GetModelDataResource().Load(&m_skinModelData, nullptr, filePath);
	m_skinModel.Init(&m_skinModelData);
	m_light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_skinModel.SetLight(&m_light);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	return true;
}

void Sky::Update()
{
	float radAngle = cPI / 180.0f * 0.03f;
	D3DXQUATERNION multi;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), radAngle);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void Sky::Draw()
{
	DWORD cullModeBackup;
	GetEngine().GetDevice()->GetRenderState(D3DRS_CULLMODE, &cullModeBackup);
	GetEngine().GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_skinModel.Draw(&GetGameScene().GetCamera().GetViewMatrix(), &GetGameScene().GetCamera().GetProjectionMatrix());
	GetEngine().GetDevice()->SetRenderState(D3DRS_CULLMODE, cullModeBackup);
}