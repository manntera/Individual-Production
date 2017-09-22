#include "stdafx.h"
#include "GameScene.h"
#include "../../GameCamera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../test.h"
#include "../../Map/Sky.h"
#include "../../GameCamera/GameCamera.h"
#include "../../Map/Map.h"

GameScene *g_gameScene;

void GameScene::Init()
{
	m_test = New<Test>();
	m_test->Init({ 0.0f, 30.0f, 0.0f });
	m_test = New<Test>();
	m_test->Init({ 0.0f, 50.0f, 0.0f });
	m_sky = New<Sky>();
	m_map = New<Map>();
	m_map->Init();
	m_camera = New<GameCamera>();
	m_camera->Init();

}

void GameScene::Update()
{

}

Player* GameScene::GetPlayer()
{
	return m_map->GetPlayer();
}

Camera& GameScene::GetCamera()
{
	return m_camera->GetCamera();
}

