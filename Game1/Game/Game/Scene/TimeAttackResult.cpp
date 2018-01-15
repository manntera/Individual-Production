#include "stdafx.h"
#include "TimeAttackResult.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"

TimeAttackResult::TimeAttackResult()
{
	m_time = 0.0f;
}

TimeAttackResult::~TimeAttackResult()
{
	g_pFade->FadeOut();
}

void TimeAttackResult::Init(float time)
{
	m_time = time;
}

bool TimeAttackResult::Start()
{
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/TitleBack.png");
	m_back.Init(texture);
	m_back.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	for (int i = 0; i < NUM_MAX; i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/%d.png", i);
		m_numTexture[i] = GetTextureResource().LoadTexture(filePath);
	}
	D3DXVECTOR2 spritePos = { -300.0f, 100.0f };
	texture = GetTextureResource().LoadTexture("Assets/sprite/ClearTime.png");
	m_timeSprite.Init(texture);
	m_timeSprite.SetSize({ 640.0f, 120.0f });
	m_timeSprite.SetPosition(spritePos);
	spritePos.x += 330.0f;
	texture = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
	for (int i = 0; i < TIME_MAX; i++)
	{
		spritePos.x -= 3.0f;
		m_colonSprite[i].Init(texture);
		m_colonSprite[i].SetSize({ 60.0f, 160.0f });
		m_colonSprite[i].SetPosition(spritePos);
		spritePos.x +=55.0f;
		for (int j = 0; j < DIGIT_MAX; j++)
		{
			m_numSprite[i][j].Init(m_numTexture[0]);
			m_numSprite[i][j].SetPosition(spritePos);
			m_numSprite[i][j].SetSize({ 80.0f, 120.0f });
			spritePos.x += 80.0f;
		}
	}
	int time = (int)(m_time * 100.0f);
	for (int i = DIGIT_MAX * TIME_MAX - 1; 0 <= i; i--)
	{
		m_numSprite[0][i].SetTexture(m_numTexture[time % 10]);
		time /= 10;
	}

	texture = GetTextureResource().LoadTexture("Assets/sprite/Retry.png");
	m_retry.Init(texture);
	m_retry.SetPosition({ 100.0f, -100.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/Finish.png");
	m_finish.Init(texture);
	m_finish.SetPosition({ 100.0f, -200.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({ -200.0f, -100.0f });

	g_pFade->FadeIn();
	return true;
}

void TimeAttackResult::Update()
{
	if (!g_pFade->IsExcute())
	{
		if (g_pFade->GetCurrentState() == enFadeOut)
		{
			if (m_choiceNum == 1)
			{
				New<TitleScene>(0);
			}
			else
			{
				g_gameScene = New<GameScene>(0);
				g_gameScene->Init(g_gameScene->GetStageNum(), true);
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
	}
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		m_choiceNum++;
	}
	m_choiceNum %= 2;
	m_arrow.SetPosition({ -200.0f, -100.0f + -100.0f * m_choiceNum });
	if (GetPad().IsPressButton(enButtonA))
	{

		g_pFade->FadeOut();
	}
}

void TimeAttackResult::Draw()
{
	m_back.Draw();
	for (int i = 0; i < TIME_MAX * DIGIT_MAX; i++)
	{
		m_numSprite[0][i].Draw();
	}
	for (int i = 0; i < TIME_MAX; i++)
	{
		m_colonSprite[i].Draw();
	}
	m_timeSprite.Draw();
	m_retry.Draw();
	m_finish.Draw();
	m_arrow.Draw();
}