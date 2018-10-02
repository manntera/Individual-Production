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
#include "../GhostPlayer/GhostDataListManager.h"


GameScene::GameScene() :
	m_isGameOver(false),

	m_isGameClear(false),
	m_pMap(nullptr),
	m_pCamera(nullptr),
	m_pSky(nullptr),
	m_pBgm(nullptr),
	m_stageNum(0),
	m_stageMaxNum(5),
	m_pTimeSprite(nullptr),
	m_isInit(false),
	m_isTimeAttack(false),
	m_pGhost(nullptr),
	m_isActive(false),
	m_isLoad(false),
	m_isTimeAttackStart(true),
	m_pSprite(nullptr)
	
{
}

GameScene::~GameScene()
{
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
	if (GetFade().IsExcute())
	{
		return false;
	}
	static bool isInit = true;
	if (isInit)
	{
		m_pSky = New<Sky>(0);
		m_pSky->Init(m_stageNum);
		m_pMap = New<Map>(0);
		m_pCamera = New<GameCamera>(CAMERA_PRIORITY);
		m_pMap->Init(m_stageNum);
		m_pCamera->Init();
		m_pBgm = New<SoundSource>(0);
		m_pBgm->Init("Assets/sound/candybuke2.wav");
		m_pBgm->SetVolume(0.7f);
		m_pBgm->Play(true);
		//タイムアタックモードならタイム表示のスプライトとゴーストを出す
		if (m_isTimeAttack)
		{
			m_pGhost = New<GhostPlayer>(PLAYER_PRIORITY);
			m_pTimeSprite = New<TimeSprite>(LAST_PRIORITY);
			m_pMap->GetPlayer()->GhostDataStart();
			GetGhostDataListManager().SetIsActive(false);
			m_pTimeSprite->SetIsActive(false);
			m_pMap->SetIsPlayerActive(false);
			m_pGhost->SetIsActive(false);
			m_pSprite.reset(new Sprite);
			Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/TimeAttackStart.png");
			m_pSprite->Init(texture);
			
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
		if (m_isTimeAttack)
		{
			if (m_isTimeAttackStart)
			{

				static float m_alpha = 1.0f;
				static float alphaSpeed = 0.03f;
				if (m_alpha < 0.0f && alphaSpeed < 0.0f || 1.0f < m_alpha && 0.0f < alphaSpeed)
				{
					alphaSpeed *= -1.0f;
				}
				m_alpha += alphaSpeed;
				m_pSprite->SetAlpha(m_alpha);
				if (GetPad().IsPressButton(enButtonA))
				{
					m_pTimeSprite->SetIsActive(true);
					m_pMap->SetIsPlayerActive(true);
					if (m_pGhost != nullptr)
					{
						m_pGhost->SetIsActive(true);
					}
					GetGhostDataListManager().SetIsActive(true);
					m_pSprite.release();
					m_isTimeAttackStart = false;
				}
			}
		}
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
	m_isTimeAttackStart = true;
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

void GameScene::AfterDraw()
{
	if (m_pSprite)
	{
		m_pSprite->Draw();
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
	if (m_isTimeAttack)
	{
		m_pTimeSprite->SetIsActive(false);
	}
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
