#include "stdafx.h"
#include "GameClearScene.h"
#include "GameScene.h"
#include "Fade.h"

GameClearScene::GameClearScene()
{


}

GameClearScene::~GameClearScene()
{
	g_pFade->FadeOut();
}

void GameClearScene::Start()
{
	m_sprite.Init("Assets/sprite/CLEAR.png");
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	g_pFade->FadeIn();
}

void GameClearScene::Update()
{
	if (!g_pFade->IsExcute())
	{
		if (g_pFade->GetCurrentState() == enFadeOut)
		{
			g_gameScene = New<GameScene>(0);
			Delete(this);
		}
	}
	else
	{
		return;
	}
	if (GetPad().IsPressButton(enButtonA))
	{

		g_pFade->FadeOut();
	}
}

void GameClearScene::Draw()
{
	m_sprite.Draw();
}