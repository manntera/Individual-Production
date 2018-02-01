#include"stdafx.h"
#include "StopTimeItem.h"
#include "../../Scene/GameScene.h"
#include "../Map.h"
#include "../../Player/Player.h"

void StopTimeItem::Update()
{
	MapChip::Update();
	D3DXQUATERNION multi;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 3.0f * cPI / 180.0f);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	D3DXVECTOR3 distance = g_gameScene->GetPlayer()->GetPosition() - m_position;
	if (D3DXVec3Length(&distance) < 8.0f)
	{
		m_pMap->StopTime();
		MapChipDelete();
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}