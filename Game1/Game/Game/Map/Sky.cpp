#include "stdafx.h"
#include "Sky.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"

Sky::Sky() :
	m_skinModel(),
	m_skinModelData(),
	m_light()
{

}

Sky::~Sky()
{

}

bool Sky::Start()
{

	GetModelDataResource().Load(&m_skinModelData, nullptr, "Assets/modelData/SkyBox1.X");
	m_skinModel.Init(&m_skinModelData);
	m_light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_skinModel.SetLight(&m_light);
	return true;
}

void Sky::Update()
{
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 position = { 0.0f, 0.0f, 0.0f };
	float scaleValue = 1.0f;
	D3DXVECTOR3 scale = { scaleValue, scaleValue, scaleValue };
	m_skinModel.Update(position, rotation, scale);
}

void Sky::Draw()
{
	DWORD cullModeBackup;
	GetEngine().GetDevice()->GetRenderState(D3DRS_CULLMODE, &cullModeBackup);
	GetEngine().GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_skinModel.Draw(&GetGameScene().GetCamera().GetViewMatrix(), &GetGameScene().GetCamera().GetProjectionMatrix());
	GetEngine().GetDevice()->SetRenderState(D3DRS_CULLMODE, cullModeBackup);
}