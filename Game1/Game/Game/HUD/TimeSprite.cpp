#include "stdafx.h"
#include "TimeSprite.h"

TimeSprite::TimeSprite() :
	m_timeSprite(),
	m_colonSprite{},
	m_numSprite{},
	m_numTexture{},
	m_time(0.0f)
{
}

TimeSprite::~TimeSprite()
{

}

bool TimeSprite::Start()
{
	//数字のテクスチャを読み込み
	for (int i = 0; i < NUM_MAX; i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/%d.png", i);
		m_numTexture[i] = GetTextureResource().LoadTexture(filePath);
	}
	//スプライトを初期化
	D3DXVECTOR2 spritePos = { -510.0f, 325.0f };
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/Time.png");
	m_timeSprite.Init(texture);
	m_timeSprite.SetSize({ 250.0f, 100.0f });
	m_timeSprite.SetPosition(spritePos);
	spritePos.x += 145.0f;
	spritePos.y -= 5.0f;
	texture = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
	Texture* textures[TIME_MAX - 1];
	textures[0] = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
	textures[1] = GetTextureResource().LoadTexture("Assets/sprite/period.png");

	for (int i = 0; i < TIME_MAX; i++)
	{
		for (int j = 0; j < DIGIT_MAX; j++)
		{
			m_numSprite[i][j].Init(m_numTexture[0]);
			m_numSprite[i][j].SetPosition(spritePos);
			m_numSprite[i][j].SetSize({ 50.0f, 80.0f });
			spritePos.x += 43.0f;
		}
		if (i == TIME_MAX - 1)
		{
			break;
		}
		if (i == 0)
		{
			spritePos.x -= 15.0f;
			m_colonSprite[i].Init(textures[i]);
			m_colonSprite[i].SetSize({ 44.0f, 100.0f });
			m_colonSprite[i].SetPosition(spritePos);
			spritePos.x += 27.0f;
		}
		else if(i == 1)
		{
			spritePos.x -= 10.0f;
			m_colonSprite[i].Init(textures[i]);
			m_colonSprite[i].SetSize({ 25.0f, 100.0f });
			m_colonSprite[i].SetPosition(spritePos);
			spritePos.x += 20.0f;
		}
	}
	return true;
}

void TimeSprite::Update()
{
	m_time += 1.0f / 60.0f;
	//60秒以上経っていたら1分にするために桁を繰り上げ
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

void TimeSprite::AfterDraw()
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