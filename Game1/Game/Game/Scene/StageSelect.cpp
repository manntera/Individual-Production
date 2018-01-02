#include "stdafx.h"
#include "StageSelect.h"
#include "Fade.h"
#include "GameScene.h"
#include "TitleScene.h"

StageSelect::StageSelect()
{
	m_choiceNum = 0;
	m_isBackScene = false;
}

StageSelect::~StageSelect()
{

}

bool StageSelect::Start()
{
	if (g_pFade->IsExcute())
	{
		return false;
	}
	Texture* texture;
	D3DXVECTOR2 position = { 0.0f, 500.0f };
	for (int i = 0;i < 5;i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/stage%d.png", i + 1);
		texture = GetTextureResource().LoadTexture(filePath);
		m_stageNum[i].Init(texture);
		m_stageNum[i].SetPosition(position);
		position.y -= 200.0f;
	}
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({ -600.0f, 500.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/TitleBack.png");
	m_back.Init(texture);
	m_back.SetSize({ (float)FRAME_BUFFER_WIDTH, (float)FRAME_BUFFER_HEIGHT });
	g_pFade->FadeIn();
	return true;
}

void StageSelect::Update()
{
	if (!g_pFade->IsExcute())
	{
		if (g_pFade->GetCurrentState() == enFadeOut)
		{
			if (m_isBackScene)
			{
				New<TitleScene>(0);
			}
			else
			{
				g_gameScene = New<GameScene>(0);
				g_gameScene->Init(m_choiceNum, true);
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
		g_pFade->FadeOut();
	}
	else if (GetPad().IsTriggerButton(enButtonB))
	{
		g_pFade->FadeOut();
		m_isBackScene = true;
	}

	if (GetPad().IsTriggerButton(enButtonUp))
	{
		m_choiceNum--;
		if (m_choiceNum < 0)
		{
			m_choiceNum = GameScene::GetStageNum();
		}
	}
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		m_choiceNum++;
	}

	if (GameScene::GetStageNum() != 0)
	{
		m_choiceNum %= GameScene::GetStageNum();
	}
	else
	{
		m_choiceNum %= 1;
	}
	m_arrow.SetPosition({ -600.0f, 500.f + -200.0f * m_choiceNum });
}

void StageSelect::Draw()
{
	m_back.Draw();
	for (int i = 0;i < GameScene::GetStageNum();i++)
	{
		m_stageNum[i].Draw();
	}
	m_arrow.Draw();
}