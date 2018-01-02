#include "stdafx.h"
#include"GameOverScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"


GameOverScene::GameOverScene()
{

}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::Start()
{
	if (g_pFade->IsExcute())
	{
		return false;
	}
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/GAMEOVER.png");
	m_sprite.Init(texture);
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	g_pFade->FadeIn();
	return true;
}

void GameOverScene::Update()
{
	if (!g_pFade->IsExcute())
	{
		if (g_pFade->GetCurrentState() == enFadeOut)
		{
			New<TitleScene>(0);
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

void GameOverScene::Draw()
{
	m_sprite.Draw();
}