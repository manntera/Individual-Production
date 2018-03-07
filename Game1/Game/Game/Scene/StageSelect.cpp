#include "stdafx.h"
#include "StageSelect.h"
#include "Fade.h"
#include "TitleScene.h"

StageSelect::StageSelect() :
	m_stageNum{},
	m_arrow(),
	m_back(),
	m_choiceNum(0),
	m_isBackScene(false),
	m_pBgm(nullptr)
{
}

StageSelect::~StageSelect()
{

}

bool StageSelect::Start()
{

	if (GetFade().IsExcute())
	{
		return false;
	}
	Texture* texture;
	D3DXVECTOR2 position = { 0.0f, 250.0f };
	for (int i = 0;i < STAGE_NUM;i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/stage%d.png", i + 1);
		texture = GetTextureResource().LoadTexture(filePath);
		m_stageNum[i].Init(texture);
		m_stageNum[i].SetPosition(position);
		position.y -= 100.0f;
	}
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({ -300.0f, 250.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/TitleBack.png");
	m_back.Init(texture);
	m_back.SetSize({ (float)FRAME_BUFFER_WIDTH, (float)FRAME_BUFFER_HEIGHT });
	GetFade().FadeIn();
	return true;
}

void StageSelect::Update()
{
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			if (m_isBackScene)
			{
				TitleScene* title = New<TitleScene>(0);
				if (m_pBgm != nullptr)
				{
					title->SetBGM(m_pBgm);
				}
			}
			else
			{
				GetGameScene().Create();
				GetGameScene().Init(m_choiceNum, true);
				if (m_pBgm != nullptr)
				{
					Delete(m_pBgm);
				}
			}
			Delete(this);
		}
	}
	else
	{
		return;
	}

	//‘I‘ğ‚ğŒˆ’è
	if (GetPad().IsPressButton(enButtonA))
	{
		GetFade().FadeOut();
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/enter2.wav");
		sound->Play(false);
	}
	//ƒLƒƒƒ“ƒZƒ‹
	else if (GetPad().IsTriggerButton(enButtonB))
	{
		GetFade().FadeOut();
		m_isBackScene = true;		
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/cancel.wav");
		sound->Play(false);
	}
	//–îˆó‚ğã‚É“®‚©‚·
	if (GetPad().IsTriggerButton(enButtonUp))
	{
		m_choiceNum--;
		if (m_choiceNum < 0)
		{
			m_choiceNum = GetGameScene().GetStageMaxNum() - 1;
		}
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
	}
	//–îˆó‚ğ‰º‚É“®‚©‚·
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		m_choiceNum++;
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
	}

	if (GetGameScene().GetStageMaxNum() != 0)
	{
		m_choiceNum %= GetGameScene().GetStageMaxNum();
	}
	else
	{
		m_choiceNum %= 1;
	}
	m_arrow.SetPosition({ -300.0f, 250.f + -100.0f * m_choiceNum });
}

void StageSelect::Draw()
{
	m_back.Draw();
	for (int i = 0;i < GetGameScene().GetStageMaxNum();i++)
	{
		m_stageNum[i].Draw();
	}
	m_arrow.Draw();
}