#include "stdafx.h"
#include "GhostPlayer.h"
#include "../Scene/GameScene.h"
#include "../GameCamera/GameCamera.h"
#include "../Player/Player.h"
#include "GhostDataListManager.h"

GhostPlayer::GhostPlayer()
{
}

GhostPlayer::~GhostPlayer()
{

}

bool GhostPlayer::Start()
{
	//ゴーストデータが空の場合デリート
	if (g_ghostDataList->GetGhostData().empty())
	{
		g_gameScene->GhostDataFinish();
		return true;
	}
	Player* player = g_gameScene->GetPlayer();
	m_modelData.CloneModelData(player->GetSkinModelData(), &m_animation);
	m_model.Init(&m_modelData);
	m_model.SetLight(&player->GetLight());
	m_ghostData = g_ghostDataList->GetGhostData().begin();
	m_animation.PlayAnimation(m_ghostData->currentAnimationNum);
	m_currentAnimationNum = m_ghostData->currentAnimationNum;
	return true;
}


void GhostPlayer::Update()
{
	m_model.Update(m_ghostData->position, m_ghostData->rotation, {1.0f, 1.0f, 1.0f});
	if (m_currentAnimationNum != m_ghostData->currentAnimationNum)
	{
		m_currentAnimationNum = m_ghostData->currentAnimationNum;
		m_animation.PlayAnimation(m_currentAnimationNum);
	}
	m_animation.Update(m_ghostData->animationUpdateTime);
	m_ghostData++;
}

void GhostPlayer::Draw()
{
	Camera& camera = g_gameScene->GetCamera();
	m_model.Draw(&camera.GetViewMatrix(), &camera.GetProjectionMatrix());
}