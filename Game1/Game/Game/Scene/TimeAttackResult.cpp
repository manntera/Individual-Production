#include "stdafx.h"
#include "TimeAttackResult.h"
#include "TitleScene.h"
#include "Fade.h"

int TimeAttackResult::m_times[STAGE_NUM][RANK_NUM] = {};

TimeAttackResult::TimeAttackResult() :
	m_choiceNum(0),
	m_arrow(),
	m_finish(),
	m_retry(),
	m_rankNum(0),
	m_back(),
	m_colonSprite{},
	m_numSprite{},
	m_numTexture{},
	m_alpha(0.0f),
	m_stageNum(GetGameScene().GetStageNum())
{
}

TimeAttackResult::~TimeAttackResult()
{

}

void TimeAttackResult::Init(float time)
{


	//今回のタイムをランキングの中でソート
	int times[RANK_NUM + 1];
	times[RANK_NUM] = (int)(time * 100.0f);
	memcpy(times, m_times[m_stageNum], sizeof(m_times[m_stageNum]));
	int i;
	for (i = RANK_NUM;0 < i;i--)
	{
		if (times[i] < times[i - 1])
		{
			int swap = times[i];
			times[i] = times[i - 1];
			times[i - 1] = swap;
		}
		else
		{
			break;
		}
	}
	memcpy(m_times[m_stageNum], times, sizeof(m_times[m_stageNum]));
	m_rankNum = i;
}

bool TimeAttackResult::Start()
{
	if (GetFade().IsExcute())
	{
		return false;
	}
	//スプライトを初期化
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/TimeAttackBack.png");
	m_back.Init(texture);
	m_back.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
	for (int i = 0; i < NUM_MAX; i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/sprite/%d.png", i);
		m_numTexture[i] = GetTextureResource().LoadTexture(filePath);
	}
	for (int k = 0;k < RANK_NUM;k++)
	{
		D3DXVECTOR2 spritePos = { 20.0f, 290.0f + -120.0f * k };
		for (int i = 0; i < TIME_MAX; i++)
		{
			float addX = 0.0f;
			float subX = 0.0f;
			switch (i)
			{
			case 0:
				texture = m_numTexture[k + 1];
				addX = 100.0f;
				break;
			case 1:
				texture = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
				addX = 50.0f;
				subX = -30.0f;
				break;
			case 2:
				texture = GetTextureResource().LoadTexture("Assets/sprite/period.png");
				addX = 40.0f;
				subX = -20.0f;
				break;
			}
			spritePos.x += subX;
			m_colonSprite[k][i].Init(texture);
			m_colonSprite[k][i].SetSize({ 75.0f, 150.0f });
			m_colonSprite[k][i].SetPosition(spritePos);
			if (i == 2)
			{
				m_colonSprite[k][i].SetSize({ 50.0f, 100.0f });
				m_colonSprite[k][i].SetPosition({spritePos.x, spritePos.y - 20.0f});
			}
			spritePos.x += addX;
			for (int j = 0; j < DIGIT_MAX; j++)
			{
				m_numSprite[k][i][j].Init(m_numTexture[0]);
				m_numSprite[k][i][j].SetPosition(spritePos);
				m_numSprite[k][i][j].SetSize({ 100.0f, 150.0f });
				spritePos.x += 82.0f;
			}
		}
		int time = m_times[m_stageNum][k];
		for (int i = DIGIT_MAX * TIME_MAX - 1; 0 <= i; i--)
		{
			m_numSprite[k][0][i].SetTexture(m_numTexture[time % 10]);
			time /= 10;
		}
	}

	texture = GetTextureResource().LoadTexture("Assets/sprite/Retry.png");
	m_retry.Init(texture);
	m_retry.SetPosition({ -300.0f, -100.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/Finish.png");
	m_finish.Init(texture);
	m_finish.SetPosition({ -100.0f, -200.0f });
	texture = GetTextureResource().LoadTexture("Assets/sprite/arrow.png");
	m_arrow.Init(texture);
	m_arrow.SetPosition({ -550.0f, -100.0f });
	GetFade().FadeIn();
	return true;
}

void TimeAttackResult::Update()
{
	//フェードアウトの状態でフェードが終わったら遷移する
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			//タイトルへを選んでいたらタイトルへ遷移
			if (m_choiceNum == 1)
			{
				New<TitleScene>(0);
			}
			else
			{
				GetGameScene().Create();
				GetGameScene().Init(GetGameScene().GetStageNum(), true);
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
	m_arrow.SetPosition({ -550.0f, -100.0f + -100.0f * m_choiceNum });
	//選択を決定
	if (GetPad().IsPressButton(enButtonA))
	{

		GetFade().FadeOut();
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/enter2.wav");
		sound->Play(false);
	}
	//ランク内であればアルファ値を変えて点滅させる
	if (m_rankNum != RANK_NUM)
	{
		static float alphaSpeed = 0.03f;
		if (m_alpha < 0.0f && alphaSpeed < 0.0f || 1.0f < m_alpha && 0.0f < alphaSpeed)
		{
			alphaSpeed *= -1.0f;
		}
		m_alpha += alphaSpeed;
		for (int i = 0;i < TIME_MAX;i++)
		{
			if (i != 0)
			{
				m_colonSprite[m_rankNum][i].SetAlpha(m_alpha);
			}
			for (int j = 0;j < DIGIT_MAX;j++)
			{
				m_numSprite[m_rankNum][i][j].SetAlpha(m_alpha);
			}
		}
	}
}

void TimeAttackResult::Draw()
{
	m_back.Draw();
	for (int i = 0; i < RANK_NUM; i++)
	{
		for (int j = 0;j < TIME_MAX;j++)
		{
			for (int k = 0;k < DIGIT_MAX;k++)
			{
				m_numSprite[i][j][k].Draw();
			}
			m_colonSprite[i][j].Draw();
		}
	}
	m_retry.Draw();
	m_finish.Draw();
	m_arrow.Draw();
}

void TimeAttackResult::TimeDataRead()
{
	//ランキングのタイムを初期化
	FILE* file;
	const int DATA_MAX = 5;
	file = fopen("Assets/SaveData/Time.bin", "rb");
	char data[DATA_MAX + 1];
	for (int i = 0;i < STAGE_NUM;i++)
	{
		for (int j = 0;j < RANK_NUM;j++)
		{
			fgets(data, DATA_MAX + 1, file);
			int inNum = 0;
			for (int k = 0;k < DATA_MAX;k++)
			{
				inNum *= 10;
				inNum += data[k] - '0';
			}
			m_times[i][j] = inNum;
		}
	}
	fclose(file);
}

void TimeAttackResult::TimeDataSave()
{
	FILE* file;
	file = fopen("Assets/SaveData/Time.bin", "wb");
	for (int i = 0;i < STAGE_NUM;i++)
	{
		for (int j = 0;j < RANK_NUM;j++)
		{
			fprintf(file, "%05d", m_times[i][j]);
		}
	}
	fclose(file);
}