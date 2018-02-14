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


GameScene::GameScene() :
	m_isGameOver(false),
	m_isGameClear(false),
	m_pMap(nullptr),
	m_pCamera(nullptr),
	m_pSky(nullptr),
	m_pBgm(nullptr),
	m_stageNum(0),
	m_stageMaxNum(4),
	m_pTimeSprite(nullptr),
	m_isInit(false),
	m_isTimeAttack(false),
	m_pGhost(nullptr),
	m_isActive(false),
	m_isLoad(false)
	
{
}

GameScene::~GameScene()
{
	Reset();
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
	static bool isInit = true;
	if (isInit)
	{
		m_pSky = New<Sky>(0);
		m_pMap = New<Map>(0);
		m_pCamera = New<GameCamera>(CAMERA_PRIORITY);
		m_pMap->Init(m_stageNum);
		m_pCamera->Init();
		m_pBgm = New<SoundSource>(0);
		m_pBgm->Init("Assets/sound/GameBgm.wav");
		m_pBgm->SetVolume(0.1f);
		m_pBgm->Play(true);
		if (m_isTimeAttack)
		{
			m_pGhost = New<GhostPlayer>(PLAYER_PRIORITY);
			const Player* player = m_pMap->GetPlayer();
			m_pTimeSprite = New<TimeSprite>(LAST_PRIORITY);
			player->GhostDataStart();
		}
		m_isGameClear = false;
		m_isGameOver = false;
		isInit = false;
		return false;
	}
	else
	{
		if (m_isLoad)
		{
			GetFade().FadeIn();
			isInit = true;
			return true;
		}
		else
		{
			return false;
		}
	}
}

void GameScene::Update()
{
	//フェードアウトの状態でフェードが終わると遷移する
	if (!GetFade().IsExcute())
	{
		if (GetFade().GetCurrentState() == enFadeOut)
		{
			//ゲームクリアしたとき
			if (m_isGameClear)
			{
				if (!m_isTimeAttack)
				{
					New<GameClearScene>(0);
					if (m_stageNum < STAGE_NUM)
					{
						if (m_stageNum == m_stageMaxNum)
						{
							m_stageMaxNum++;
						}
						m_stageNum++;
					}
				}
				else
				{
					TimeAttackResult* result = New<TimeAttackResult>(0);
					result->Init(m_pTimeSprite->GetTime());
					m_pMap->GetPlayer()->GhostDataFinish(m_pTimeSprite->GetTime(), true);
				}
			}
			else if (m_isGameOver)	//ゲームオーバーの時
			{
				GameOverScene* gameOver = New<GameOverScene>(0);
				gameOver->Init(m_isTimeAttack);
				
			}
			if (m_pGhost != nullptr)
			{
				Delete(m_pGhost);
				m_pGhost = nullptr;
			}
			Delete(this);
			m_isActive = false;
		}
	}
}

const Player* GameScene::GetPlayer() const
{
	return m_pMap->GetPlayer();
}

const Camera& GameScene::GetCamera() const
{
	return m_pCamera->GetCamera();
}

void GameScene::BeforeDead()
{
	if (m_pBgm != nullptr)
	{
		Delete(m_pBgm);
		m_pBgm = nullptr;
	}
	if (m_pTimeSprite != nullptr)
	{
		Delete(m_pTimeSprite);
		m_pTimeSprite = nullptr;
	}
	GhostDataFinish();
	m_isInit = false;
	m_isLoad = false;
	m_isTimeAttack = false;
	if (m_pMap != nullptr)
	{
		Delete(m_pMap);
		m_pMap = nullptr;
	}
	if (m_pSky != nullptr)
	{
		Delete(m_pSky);
		m_pSky = nullptr;
	}
	if (m_pCamera != nullptr)
	{
		Delete(m_pCamera);
		m_pCamera = nullptr;
	}
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
	GetFade().FadeOut();
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
	GetFade().FadeOut();
	SoundSource* sound = New<SoundSource>(0);
	sound->Init("Assets/sound/univ0010.wav");
	sound->Play(false);
	if (m_isTimeAttack)
	{
		m_pMap->GetPlayer()->GhostDataFinish(m_pTimeSprite->GetTime(), false);
	}
}
