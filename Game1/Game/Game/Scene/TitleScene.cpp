#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Fade.h"
#include "StageSelect.h"

TitleScene::TitleScene() :
	m_titleBack(),
	m_title(),
	m_start(),
	m_continue(),
	m_timeAttack(),
	m_arrow(),
	m_choiceNum(0)
{

}

TitleScene::~TitleScene()
{
}

bool TitleScene::Start()
{

	if (GetFade().IsExcute())
	{
		true;
	}
	//スプライトを初期化
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/TitleBack.png");
	m_titleBack.Init(texture);
	m_titleBack.SetSize({(float)FRAME_BUFFER_WIDTH, (float)FRAME_BUFFER_HEIGHT});
	texture = GetTextureResource().LoadTexture("Assets/sprite/Title.png");
	m_title.Init(texture);
	m_title.SetPosition({ 00.0f, 200.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/start.png");
	m_start.Init(texture);
	m_start.SetPosition({ 100.0f, -100.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/continue.png");
	m_continue.Init(texture);
	m_continue.SetPosition({100.0f, -200.0f});
	texture = GetTextureResource().LoadTexture("Assets/sprite/TimeAttack.png");
	m_timeAttack.Init(texture);
	m_timeAttack.SetPosition({ 200.0f, -300.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({ -275.0f, -100.0f });
	m_arrow.SetSize({ 100.0f, 100.0f });
	GetFade().FadeIn();
	return true;
}

void TitleScene::Update()
{
	//フェードアウトの状態でフェードが終わると遷移する
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			switch (m_choiceNum)
			{
			case enSceneStart:
				GetGameScene().Create();
				GetGameScene().Init(0, false);
				break;
			case enSceneContinue:
				GetGameScene().Create();
				GetGameScene().Init(GetGameScene().GetStageNum(), false);
				break;
			case enSceneTimeAttack:
				New<StageSelect>(0);
				break;
			default:
				break;
			}
			Delete(this);
		}
	}
	else
	{
		return;
	}
	if (GetPad().IsPressButton(enButtonA))
	{
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/enter2.wav");
		sound->Play(false);
		GetFade().FadeOut();
	}
	if (GetPad().IsTriggerButton(enButtonUp))
	{
		m_choiceNum--;
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
		if (m_choiceNum < 0)
		{
			m_choiceNum = enSceneTimeAttack;
		}
	}
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
		m_choiceNum++;
	}

	//if (GameScene::GetStageNum() != 0)
	{
		m_choiceNum %= 3;
	}
	//else
	//{
	//	m_choiceNum %= 1;
	//}
	m_arrow.SetPosition({ -275.0f, -100.f + -100.0f * m_choiceNum });
}

void TitleScene::AfterDraw()
{
	m_titleBack.Draw();
	m_title.Draw();
	m_start.Draw();
	m_arrow.Draw();
	//if (GameScene::GetStageNum() != 0)
	{
		m_continue.Draw();
		m_timeAttack.Draw();
	}
}

