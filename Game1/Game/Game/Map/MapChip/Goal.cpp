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

void Goal::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	m_light.SetAmbiemtLight({ 70.0f, 70.0f, 1.0f, 1.0f });
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void Goal::Update()
{
	MapChip::Update();
	if (!GetGameScene().IsActive())
	{
		return;
	}
	//プレイヤーがある一定の距離範囲内に入ったらゴール
	const Player* player = GetGameScene().GetPlayer();
	D3DXVECTOR3 distance = player->GetPosition() - m_position;
	if (D3DXVec3Length(&distance) < 12.0f)
	{
		GetGameScene().GameClear();
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
