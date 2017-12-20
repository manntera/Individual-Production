#include "stdafx.h"
#include "Goal.h"
#include "../../Scene/GameScene.h"
#include "../../Player/Player.h"

Goal::Goal()
{
}

Goal::~Goal()
{

}

void Goal::Update()
{
	if (g_gameScene == nullptr)
	{
		return;
	}
	Player* player = g_gameScene->GetPlayer();
	D3DXVECTOR3 distance = player->GetPosition() - m_position;
	if (D3DXVec3Length(&distance) < 6.0f)
	{
		g_gameScene->GameClear();
	}
	MapChip::Update();
}

