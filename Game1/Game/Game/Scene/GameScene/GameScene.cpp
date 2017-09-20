#include "stdafx.h"
#include "GameScene.h"
#include "../../GameCamera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../test.h"

GameScene *g_gameScene;

void GameScene::Init()
{
	m_test = New<Test>();
	m_test->Init({0.0f, 0.0f, 0.0f});
	m_test = New<Test>();
	m_test->Init({ 0.0f, -10.0f, 0.0f });

	m_player = New<Player>();
	m_camera = New<GameCamera>();
	m_camera->Init();
	m_player->Init();

}

void GameScene::Update()
{

}