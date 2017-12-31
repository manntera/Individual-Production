#include "stdafx.h"
#include "GameClearScene.h"
#include "GameScene.h"
#include "Fade.h"

GameClearScene::GameClearScene()
{
	m_time = 0.0f;
}

GameClearScene::~GameClearScene()
{
	g_pFade->FadeOut();
}

void GameClearScene::Init(float time)
{
	m_time = time;
}

void GameClearScene::Start()
{
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/CLEAR.png");
	m_sprite.Init(texture);
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	for (int i = 0; i < NUM_MAX; i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/%d.png", i);
		m_numTexture[i] = GetTextureResource().LoadTexture(filePath);
	}
	D3DXVECTOR2 spritePos = { -600.0f, -200.0f };
	texture = GetTextureResource().LoadTexture("Assets/sprite/ClearTime.png");
	m_timeSprite.Init(texture);
	m_timeSprite.SetSize({ 640.0f, 120.0f });
	m_timeSprite.SetPosition(spritePos);
	spritePos.x += 660.0f;
	texture = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
	for (int i = 0; i < TIME_MAX; i++)
	{
		spritePos.x -= 7.0f;
		m_colonSprite[i].Init(texture);
		m_colonSprite[i].SetSize({ 60.0f, 160.0f });
		m_colonSprite[i].SetPosition(spritePos);
		spritePos.x +=110.0f;
		for (int j = 0; j < DIGIT_MAX; j++)
		{
			m_numSprite[i][j].Init(m_numTexture[0]);
			m_numSprite[i][j].SetPosition(spritePos);
			m_numSprite[i][j].SetSize({ 80.0f, 120.0f });
			spritePos.x += 160.0f;
		}
	}
	int time = (int)(m_time * 100.0f);
	for (int i = DIGIT_MAX * TIME_MAX - 1; 0 <= i; i--)
	{
		m_numSprite[0][i].SetTexture(m_numTexture[time % 10]);
		time /= 10;
	}
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
	for (int i = 0; i < TIME_MAX * DIGIT_MAX; i++)
	{
		m_numSprite[0][i].Draw();
	}
	for (int i = 0; i < TIME_MAX; i++)
	{
		m_colonSprite[i].Draw();
	}
	m_timeSprite.Draw();
}