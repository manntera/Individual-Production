#include"stdafx.h"
#include "StopTimeItem.h"
#include "../../Scene/GameScene.h"
#include "../Map.h"
#include "../../Player/Player.h"

StopTimeItem::StopTimeItem() :
		m_isDead(false),
		m_revivalTime(0.0f)
{

}

void StopTimeItem::Update()
{
	if (!m_isActive)
	{
		return;
	}
	if (m_isDead)
	{
		m_revivalTime += GetGameTime().GetDeltaFrameTime();
		if (10.0f < m_revivalTime)
		{
			m_isDead = false;
			m_revivalTime = 0.0f;
		}
		return;
	}
	MapChip::Update();
	m_light.SetAmbiemtLight({ 0.3f, 0.3f, 0.3f, 1.0f });
	D3DXQUATERNION multi;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 3.0f * cPI / 180.0f);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//プレイヤーとの距離が一定範囲内になったら消えてマップのオブジェクトを一定時間動きを止める
	D3DXVECTOR3 distance = GetGameScene().GetPlayer()->GetPosition() - m_position;
	if (D3DXVec3Length(&distance) < 8.0f)
	{
		m_pMap->StopTime();
		m_isDead = true;
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void StopTimeItem::Draw()
{
	if (m_isDead)
	{
		return;
	}
	MapChip::Draw();
}