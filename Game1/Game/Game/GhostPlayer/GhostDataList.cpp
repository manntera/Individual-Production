#include "stdafx.h"
#include "GhostDataList.h"
#include "../Scene/GameScene.h"

GhostDataList* g_ghostDataList = nullptr;

GhostDataList::GhostDataList()
{
	m_pPosition = nullptr;
	m_pRotation = nullptr;
	m_pAnimation = nullptr;
	m_stageNum = 0;
	m_ghostData.resize(STAGE_NUM);
}

GhostDataList::~GhostDataList()
{

}

void GhostDataList::Start(D3DXVECTOR3* position, D3DXQUATERNION* rotation, Animation* animation)
{
	if (!m_ghostData.empty())
	{
		return;
	}
	m_pPosition = position;
	m_pRotation = rotation;
	m_pAnimation = animation;
	m_stageNum = g_gameScene->GetStageNum();
}

void GhostDataList::Finish()
{
	m_pPosition = nullptr;
	m_pRotation = nullptr;
	m_pAnimation = nullptr;
}

void GhostDataList::Update()
{
	if (m_pPosition == nullptr || m_pRotation == nullptr || m_pAnimation == nullptr)
	{
		return;
	}
	m_ghostData[m_stageNum].push_back({ *m_pPosition, *m_pRotation, GetGameTime().GetDeltaFrameTime(), m_pAnimation->GetCurrentAnimationNum()});
}