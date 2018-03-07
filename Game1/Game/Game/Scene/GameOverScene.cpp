#include "stdafx.h"
#include"GameOverScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"


GameOverScene::GameOverScene() :
	m_sprite(),
	m_choiceNum(0),
	m_arrow(),
	m_retry(),
	m_finish(),
	m_isTimeAttack(false)
{
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
	//選択を決定するとフェードアウトが始まり、それが終わると遷移
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			//リトライを選んでいたらもう一回ゲームシーン
			if (m_choiceNum == 0)
			{
				GetGameScene().Create();
				GetGameScene().Init(GetGameScene().GetStageNum(), m_isTimeAttack);
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
	//矢印を上に動かす
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
	//矢印を下に動かす
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		m_choiceNum++;
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
	}
	m_choiceNum %= 2;
	m_arrow.SetPosition({ -250.0f, -100.0f + -100.0f * m_choiceNum });
	//選択を決定
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