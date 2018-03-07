#include "stdafx.h"
#include "GameClearScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"

GameClearScene::GameClearScene() :
	m_sprite(),
	m_choiceNum(0),
	m_arrow(),
	m_finish(),
	m_nextStage()
{
}

GameClearScene::~GameClearScene()
{
}

bool GameClearScene::Start()
{
	if (GetFade().IsExcute())
	{
		return false;
	}
	//スプライトの初期化
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
	//選択決定でフェードアウトが始まり、それが終わったら遷移
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			//次のステージがないかタイトルへを選んでいたらタイトルに行く
			if (GetGameScene().GetStageNum() == STAGE_NUM || m_choiceNum == 1)
			{
				New<TitleScene>(0);
			}
			else
			{
				GetGameScene().Create();
				GetGameScene().Init(GetGameScene().GetStageNum(), false);
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
	m_arrow.SetPosition({ -300.0f, -100.0f + -100.0f * m_choiceNum });
	//選択を決定
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