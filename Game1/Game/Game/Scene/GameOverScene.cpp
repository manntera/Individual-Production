#include "stdafx.h"
#include"GameOverScene.h"
#include "GameScene.h"
#include "Fade.h"

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
	g_pFade->FadeIn();
}

void GameOverScene::Update()
{
	if (!g_pFade->IsExcute())
	{
		if (g_pFade->GetCurrentState() == enFadeOut)
		{
			g_gameScene = New<GameScene>();
			Delete(this);
		}
	}
	else
	{
		return;
	}
	if (GetPad().IsPressButton(padButtonA))
	{

		g_pFade->FadeOut();
	}
}

void GameOverScene::Draw()
{
	m_sprite.Draw();
}