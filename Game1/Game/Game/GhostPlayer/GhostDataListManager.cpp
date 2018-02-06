#include "stdafx.h"
#include "GhostDataListManager.h"
#include "../Scene/GameScene.h"

GhostDataListManager::GhostDataListManager() :
	m_pPosition(nullptr),
	m_pRotation(nullptr),
	m_pAnimation(nullptr),
	m_ghostData(),
	m_substitute(),
	m_stageNum(0),
	m_isActive(false)
{
	m_ghostData.resize(STAGE_NUM);
	for (int i = 0;i < STAGE_NUM;i++)
	{
		m_ghostData[i].time = 1000.0f;
	}
}

GhostDataListManager::~GhostDataListManager()
{

}

void GhostDataListManager::Start(const D3DXVECTOR3* position, const D3DXQUATERNION* rotation, const Animation* animation)
{
	m_stageNum = GetGameScene().GetStageNum();
	m_pPosition = position;
	m_pRotation = rotation;
	m_pAnimation = animation;
	m_isActive = true;
}

void GhostDataListManager::Finish(float time, bool isClear)
{
	//ゲームオーバーだった場合
	if (!isClear)
	{
		m_substitute.clear();
		m_pPosition = nullptr;
		m_pRotation = nullptr;
		m_pAnimation = nullptr;
		m_isActive = false;
		return;
	}
	//新しい記録が古い記録より早かった場合更新する
	if (time < m_ghostData[m_stageNum].time)
	{
		m_ghostData[m_stageNum].time = time;
		m_ghostData[m_stageNum].ghostData = m_substitute;
	}
	m_substitute.clear();
	m_pPosition = nullptr;
	m_pRotation = nullptr;
	m_pAnimation = nullptr;
	m_isActive = false;
}

void GhostDataListManager::Update()
{
	if (!m_isActive)
	{
		return;
	}
	m_substitute.push_back({ *m_pPosition, *m_pRotation, GetGameTime().GetDeltaFrameTime(), m_pAnimation->GetCurrentAnimationNum() });
}