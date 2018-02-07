#include "stdafx.h"
#include "TimeAttackResult.h"
#include "TitleScene.h"
#include "Fade.h"

int TimeAttackResult::m_times[STAGE_NUM][RANK_NUM + 1] = {};

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

	if (GetFade().IsExcute())
	{
		true;
	}
	//����̃^�C���������L���O�̒��Ń\�[�g
	m_times[m_stageNum][RANK_NUM] = (int)(time * 100.0f);
	int i;
	for (i = RANK_NUM;0 < i;i--)
	{
		if (m_times[m_stageNum][i] < m_times[m_stageNum][i - 1])
		{
			int swap = m_times[m_stageNum][i];
			m_times[m_stageNum][i] = m_times[m_stageNum][i - 1];
			m_times[m_stageNum][i - 1] = swap;
		}
		else
		{
			break;
		}
	}
	m_rankNum = i;
}

bool TimeAttackResult::Start()
{
	//�X�v���C�g��������
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
		D3DXVECTOR2 spritePos = { 100.0f, 270.0f + -120.0f * k};
		for (int i = 0; i < TIME_MAX; i++)
		{
			float addX = 0.0f;
			switch (i)
			{
			case 0:
				texture = m_numTexture[k + 1];
				addX = 100.0f;
				break;
			case 1:
				texture = GetTextureResource().LoadTexture("Assets/sprite/colon.png");
				addX = 40.0f;
				break;
			case 2:
				texture = GetTextureResource().LoadTexture("Assets/sprite/period.png");
				addX = 40.0f;
				break;
			}
			spritePos.x -= 30.0f;
			m_colonSprite[k][i].Init(texture);
			m_colonSprite[k][i].SetSize({ 50.0f, 100.0f });
			m_colonSprite[k][i].SetPosition(spritePos);
			spritePos.x += addX;
			for (int j = 0; j < DIGIT_MAX; j++)
			{
				m_numSprite[k][i][j].Init(m_numTexture[0]);
				m_numSprite[k][i][j].SetPosition(spritePos);
				m_numSprite[k][i][j].SetSize({ 66.0f, 100.0f });
				spritePos.x += 66.0f;
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
	//�t�F�[�h�A�E�g�̏�ԂŃt�F�[�h���I�������J�ڂ���
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			//�^�C�g���ւ�I��ł�����^�C�g���֑J��
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
	//������ɓ�����
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
	//�������ɓ�����
	if (GetPad().IsTriggerButton(enButtonDown))
	{
		m_choiceNum++;
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/select.wav");
		sound->Play(false);
	}
	m_choiceNum %= 2;
	m_arrow.SetPosition({ -550.0f, -100.0f + -100.0f * m_choiceNum });
	//�I��������
	if (GetPad().IsPressButton(enButtonA))
	{

		GetFade().FadeOut();
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/enter2.wav");
		sound->Play(false);
	}
	//�����N���ł���΃A���t�@�l��ς��ē_�ł�����
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

void TimeAttackResult::TimeInit()
{
	//�����L���O�̃^�C����5���ŏ�����
	for (int i = 0; i < STAGE_NUM;i++)
	{
		for (int j = 0;j < RANK_NUM + 1;j++)
		{
			m_times[i][j] = 50000;
		}
	}
}