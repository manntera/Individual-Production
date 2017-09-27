#include "stdafx.h"
#include "GameClearScene.h"
#include "GameScene.h"

GameClearScene::GameClearScene()
{


}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Start()
{
	m_sprite.Init("Assets/sprite/CLEAR.png");
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
}

void GameClearScene::Update()
{
	if (GetPad().IsTriggerButton(padButtonA))
	{
		g_gameScene = New<GameScene>();
		Delete(this);
	}
}

void GameClearScene::Draw()
{
	m_sprite.Draw();
}