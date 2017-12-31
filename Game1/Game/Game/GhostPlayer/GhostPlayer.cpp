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
	if (g_ghostDataList->GetGhostData().empty())
	{
		return;
	}
	m_isActive = true;
	m_modelData.CloneModelData(modelData, &m_animation);
	m_model.Init(&m_modelData);
	m_model.SetLight(light);
	m_ghostData = g_ghostDataList->GetGhostData().begin();
	m_animation.PlayAnimation(m_ghostData->currentAnimationNum);
	m_currentAnimationNum = m_ghostData->currentAnimationNum;
}

void GhostPlayer::Start()
{

}

void GhostPlayer::Update()
{
	if (!m_isActive)
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
	if (!m_isActive)
	{
		return;
	}
	Camera& camera = g_gameScene->GetCamera();
	m_model.Draw(&camera.GetViewMatrix(), &camera.GetProjectionMatrix());
}