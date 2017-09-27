#include "stdafx.h"
#include "MapChip.h"
#include "../../GameCamera/GameCamera.h"
#include "../../Scene/GameScene.h"

MapChip::MapChip()
{

}

MapChip::~MapChip()
{

}

void MapChip::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)
{
	char filePath[64];
	sprintf(filePath, "Assets/modelData/%s.X", modelName);
	m_skinModelData.LoadModelData(filePath, NULL);
	m_skinModel.Init(&m_skinModelData);
	m_light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_skinModel.SetLight(&m_light);
	m_position = position;
	m_rotation = rotation;
	m_skinModel.SetShadowCasterFlg(true);
	m_skinModel.SetShadowReceiverFlg(true);
	D3DXVECTOR3 scale = { 1.0f, 1.0f, 1.0f };
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, scale);
}

void MapChip::Start()
{
}

void MapChip::Update()
{
	m_skinModel.ShadowMapEntry();
}

void MapChip::Draw()
{
	Camera& camera = g_gameScene->GetCamera();
	m_skinModel.Draw(&camera.GetViewMatrix(), &camera.GetProjectionMatrix());
}