#include "stdafx.h"
#include "GameScene.h"
#include "../GameCamera/GameCamera.h"
#include "../Player/Player.h"
#include "../Map/Sky.h"
#include "../GameCamera/GameCamera.h"
#include "../Map/Map.h"
#include "GameClearScene.h"
#include "GameOverScene.h"

GameScene *g_gameScene;


GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Start()
{
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

void GameScene::BeforeDead()
{
	Delete(m_sky);
	Delete(m_map);
	Delete(m_camera);
}

void GameScene::GameClear()
{
	Delete(this);
	g_gameScene = nullptr;
	New<GameClearScene>();
}

void GameScene::GameOver()
{
	Delete(this);
	g_gameScene = nullptr;
	New<GameOverScene>();
}
