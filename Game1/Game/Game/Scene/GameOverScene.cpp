#include "stdafx.h"
#include"GameOverScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"


GameOverScene::GameOverScene()
{
	m_choiceNum = 0;
	m_isTimeAttack = false;
}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::Start()
{
	if (GetFade().IsExcute())
	{
		return false;
	}
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/GAMEOVER.png");
	m_sprite.Init(texture);
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	texture = GetTextureResource().LoadTexture("Assets/sprite/retry.png");
	m_retry.Init(texture);
	m_retry.SetPosition({ 0.0f, -100.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/Finish.png");
	m_finish.Init(texture);
	m_finish.SetPosition({200.0f, -200.0f});
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({ -250.0f, -100.0f });
	GetFade().FadeIn();

	return true;
}

void GameOverScene::Update()
{
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			if (m_choiceNum == 0)
			{
				g_gameScene = New<GameScene>(0);
				g_gameScene->Init(g_gameScene->GetStageNum(), m_isTimeAttack);
			}
			else
			{
				New<TitleScene>(0);
			}
			Delete(this);
		}
	}
	else
	{
		return;
	}
	if (GetPad().IsTriggerButton(enButtonUp))
	{
		m_choiceNum--;
		if (m_choiceNum < 0)
		{
			m_choiceNum = 1;
		}
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
	}
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		m_choiceNum++;
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
	}
	m_choiceNum %= 2;
	m_arrow.SetPosition({ -250.0f, -100.0f + -100.0f * m_choiceNum });
	if (GetPad().IsPressButton(enButtonA))
	{
		GetFade().FadeOut();
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/enter2.wav");
		sound->Play(false);
	}
}

void GameOverScene::Draw()
{
	m_sprite.Draw();
	m_finish.Draw();
	m_retry.Draw();
	m_arrow.Draw();
}