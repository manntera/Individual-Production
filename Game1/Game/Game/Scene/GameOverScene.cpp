#include "stdafx.h"
#include"GameOverScene.h"
#include "GameScene.h"

GameOverScene::GameOverScene()
{

}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Start()
{
	m_sprite.Init("Assets/sprite/GameOver.png");
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
}

void GameOverScene::Update()
{
	if (GetPad().IsPressButton(padButtonA))
	{
		g_gameScene = New<GameScene>();
		Delete(this);
	}
}

void GameOverScene::Draw()
{
	m_sprite.Draw();
}