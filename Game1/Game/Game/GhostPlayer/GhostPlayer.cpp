#include "stdafx.h"
#include "GhostPlayer.h"
#include "../Scene/GameScene.h"
#include "../GameCamera/GameCamera.h"
#include "GhostDataList.h"

GhostPlayer::GhostPlayer()
{
	m_isActive = false;
}

GhostPlayer::~GhostPlayer()
{

}

void GhostPlayer::Init(SkinModelData& modelData, Light* light)
{

	m_pPlayerModelData = &modelData;
	m_pLight = light;
}

bool GhostPlayer::Start()
{
	if (g_ghostDataList->GetGhostData().empty())
	{
		return true;
	}
	m_isActive = true;
	m_modelData.CloneModelData(*m_pPlayerModelData, &m_animation);
	m_model.Init(&m_modelData);
	m_model.SetLight(m_pLight);
	m_ghostData = g_ghostDataList->GetGhostData().begin();
	m_animation.PlayAnimation(m_ghostData->currentAnimationNum);
	m_currentAnimationNum = m_ghostData->currentAnimationNum;
	return true;
}


void GhostPlayer::Update()
{
	if (!m_isActive || g_gameScene == nullptr)
	{
		return;
	}
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
	if (!m_isActive || g_gameScene == nullptr)
	{
		return;
	}
	Camera& camera = g_gameScene->GetCamera();
	m_model.Draw(&camera.GetViewMatrix(), &camera.GetProjectionMatrix());
}