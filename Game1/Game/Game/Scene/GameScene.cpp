#include "stdafx.h"
#include "GameScene.h"
#include "../GameCamera/GameCamera.h"
#include "../Player/Player.h"
#include "../Map/Sky.h"
#include "../Map/Map.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "Fade.h"
#include "../HUD/TimeSprite.h"
#include "../GhostPlayer/GhostPlayer.h"
#include "TimeAttackResult.h"
GameScene *g_gameScene;
int GameScene::m_stageNum = 0;
int GameScene::m_stageMaxNum = 0;


GameScene::GameScene()
{
	m_isGameClear = false;
	m_isGameOver = false;
	m_pTimeSprite = nullptr;
	m_pGhost = nullptr;
	m_isInit = false;
	m_isTimeAttack = false;
}

GameScene::~GameScene()
{
	Delete(m_bgm);
	if (m_pTimeSprite != nullptr)
	{
		Delete(m_pTimeSprite);
	}
	if (m_pGhost != nullptr)
	{
		Delete(m_pGhost);
	}
}

void GameScene::Init(int stageNum, bool isTimeAttack)
{
	if (!m_isInit)
	{
		m_stageNum = stageNum;
		if (STAGE_NUM <= m_stageNum)
		{
			m_stageNum = 0;
		}
		m_isInit = true;
	}
	m_isTimeAttack = isTimeAttack;
}

bool GameScene::Start()
{
	m_sky = New<Sky>(0);
	m_camera = New<GameCamera>(cameraPriority);
	m_camera->Init();
	m_map = New<Map>(0);
	m_map->Init(m_stageNum);
	g_pFade->FadeIn();
	m_bgm = New<SoundSource>(0);
	m_bgm->Init("Assets/sound/BGM.wav");
	m_bgm->SetVolume(0.1f);
	m_bgm->Play(true);
	if (m_isTimeAttack)
	{
		m_pGhost = New<GhostPlayer>(playerPriority);
		Player* player = m_map->GetPlayer();
		m_pTimeSprite = New<TimeSprite>(lastPriority);
		player->GhostDataStart();
	}

	return true;
}

void GameScene::Update()
{
	if (!g_pFade->IsExcute())
	{
		if (g_pFade->GetCurrentState() == enFadeOut)
		{
			if (m_isGameClear)
			{
				if (!m_isTimeAttack)
				{
					GameClearScene* gameClearScene = New<GameClearScene>(0);
					m_stageNum++;
					m_stageMaxNum++;
				}
				else
				{
					TimeAttackResult* result = New<TimeAttackResult>(0);
					result->Init(m_pTimeSprite->GetTime());
					m_map->GetPlayer()->GhostDataFinish(m_pTimeSprite->GetTime(), true);
				}
			}
			else if (m_isGameOver)
			{
				GameOverScene* gameOver = New<GameOverScene>(0);
				gameOver->Init(m_isTimeAttack);
				
			}
			Delete(this);
			g_gameScene = nullptr;
		}
	}
	else
	{
		return;
	}
}

Player* GameScene::GetPlayer()
{
	return m_map->GetPlayer();
}

Camera& GameScene::GetCamera()
{
	return m_camera->GetCamera();
}

void GameScene::BeforeDead()
{
	Delete(m_sky);
	Delete(m_map);
	Delete(m_camera);
}

void GameScene::GhostDataFinish()
{
	if (m_pGhost != nullptr)
	{
		Delete(m_pGhost);
		m_pGhost = nullptr;
	}
}

void GameScene::GameClear()
{
	if (m_isGameClear)
	{
		return;
	}
	m_isGameClear = true;
	g_pFade->FadeOut();
	SoundSource* sound = New<SoundSource>(0);
	sound->Init("Assets/sound/univ1018.wav");
	sound->Play(false);
}

void GameScene::GameOver()
{
	if (m_isGameOver)
	{
		return;
	}
	m_isGameOver = true;
	g_pFade->FadeOut();
	SoundSource* sound = New<SoundSource>(0);
	sound->Init("Assets/sound/univ0010.wav");
	sound->Play(false);
	if (m_isTimeAttack)
	{
		m_map->GetPlayer()->GhostDataFinish(m_pTimeSprite->GetTime(), false);
	}
}
