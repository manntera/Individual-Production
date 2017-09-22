#include "stdafx.h"
#include "Sky.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"

Sky::Sky()
{

}

Sky::~Sky()
{

}

void Sky::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/SkyBox.X", NULL);
	m_skinModel.Init(&m_skinModelData);
	m_light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_skinModel.SetLight(&m_light);
}

void Sky::Update()
{
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 position = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 scale = { 1.0f, 1.0f, 1.0f };
	m_skinModel.UpdateWorldMatrix(position, rotation, scale);
}

void Sky::Render()
{
	DWORD cullModeBackup;
	GetEngine().GetDevice()->GetRenderState(D3DRS_CULLMODE, &cullModeBackup);
	GetEngine().GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());
	GetEngine().GetDevice()->SetRenderState(D3DRS_CULLMODE, cullModeBackup);
}