#include "stdafx.h"
#include "PlayerDelayItem.h"
#include "../../Player/Player.h"
#include "../../Scene/GameScene.h"

void PlayerDelayItem::Update()
{
	MapChip::Update();
	D3DXQUATERNION multi;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 3.0f * cPI / 180.0f);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ªˆê’è”ÍˆÍ“à‚É‚È‚Á‚½‚çÁ‚¦‚é
	D3DXVECTOR3 distance = GetGameScene().GetPlayer()->GetPosition() - m_position;
	if (D3DXVec3Length(&distance) < 8.0f)
	{
		MapChipDelete();
		m_pPlayer->MoveSpeedDelay();
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}