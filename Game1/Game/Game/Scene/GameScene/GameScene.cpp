#include "stdafx.h"
#include "GameScene.h"
#include "../../GameCamera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../test.h"

GameScene *g_gameScene;

void GameScene::Init()
{
	m_player = New<Player>();
	m_player->Init();
	m_camera = New<GameCamera>();
	m_camera->Init();
	m_test = New<Test>();
	m_test->Init();

}

void GameScene::Update()
{

}