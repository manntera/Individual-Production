#include "stdafx.h"
#include "GameClearScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"

GameClearScene::GameClearScene()
{
	m_choiceNum = 0;
}

GameClearScene::~GameClearScene()
{
	GetFade().FadeOut();
}

bool GameClearScene::Start()
{
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/CLEAR.png");
	m_sprite.Init(texture);
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	texture = GetTextureResource().LoadTexture("Assets/sprite/NextStage.png");
	m_nextStage.Init(texture);
	m_nextStage.SetPosition({ 150.0f, -100.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/Finish.png");
	m_finish.Init(texture);
	m_finish.SetPosition({ 150.0f, -200.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({-300.0f, -100.0f});
	GetFade().FadeIn();
	return true;
}

void GameClearScene::Update()
{
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			if (GameScene::GetStageNum() == STAGE_NUM || m_choiceNum == 1)
			{
				New<TitleScene>(0);
			}
			else
			{
				g_gameScene = New<GameScene>(0);
				g_gameScene->Init(g_gameScene->GetStageNum(), false);
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
	m_arrow.SetPosition({ -300.0f, -100.0f + -100.0f * m_choiceNum });
	if (GetPad().IsPressButton(enButtonA))
	{

		GetFade().FadeOut();
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/enter2.wav");
		sound->Play(false);
	}
}

void GameClearScene::Draw()
{
	m_sprite.Draw();
	m_nextStage.Draw();
	m_finish.Draw();
	m_arrow.Draw();
}