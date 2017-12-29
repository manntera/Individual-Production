#include "stdafx.h"
#include "TimeSprite.h"

TimeSprite::TimeSprite()
{
	m_time = 350.0f;
}

TimeSprite::~TimeSprite()
{

}

void TimeSprite::Start()
{
	for (int i = 0; i < NUM_MAX; i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/%d.png", i);
		m_numTexture[i] = GetTextureResource().LoadTexture(filePath);
	}
	D3DXVECTOR2 spritePos = { -1150.0f, 670.0f };
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/Time.png");
	m_timeSprite.Init(texture);
	m_timeSprite.SetSize({ 120.0f, 45.0f });
	m_timeSprite.SetPosition(spritePos);
	spritePos.x += 120.0f;
	texture = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
	for (int i = 0; i < TIME_MAX; i++)
	{
		spritePos.x -= 7.0f;
		m_colonSprite[i].Init(texture);
		m_colonSprite[i].SetSize({ 20.0f, 60.0f });
		m_colonSprite[i].SetPosition(spritePos);
		spritePos.x += 40.0f;
		for (int j = 0; j < DIGIT_MAX; j++)
		{
			m_numSprite[i][j].Init(m_numTexture[0]);
			m_numSprite[i][j].SetPosition(spritePos);
			m_numSprite[i][j].SetSize({ 30.0f, 45.0f });
			spritePos.x += 57.0f;
		}
	}
}

void TimeSprite::Update()
{
	m_time += GetGameTime().GetDeltaFrameTime();
	int minute = (int)m_time / 10 % 10 / 6;
	if (1 <= minute)
	{
		m_time += minute * 100.0f;
		m_time -= minute * 60.0f;
	}
	int time = (int)(m_time * 100.0f);
	for (int i = DIGIT_MAX * TIME_MAX - 1; 0 <= i; i--)
	{
		m_numSprite[0][i].SetTexture(m_numTexture[time % 10]);
		time /= 10;
	}
}

void TimeSprite::Draw()
{
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