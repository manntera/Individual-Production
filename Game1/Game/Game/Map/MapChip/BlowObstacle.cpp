#include "stdafx.h"
#include "BlowObstacle.h"
#include "../../Player/Player.h"
#include "../../Scene/GameScene.h"

void BlowObstacle::Update()
{
	MapChip::Update();
	D3DXQUATERNION multi;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 3.0f * cPI / 180.0f);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	//�v���C���[�Ƃ̋��������͈͓��ɂȂ����������
	D3DXVECTOR3 distance = GetGameScene().GetPlayer()->GetPosition() - m_position;
	if (D3DXVec3Length(&distance) < 8.0f)
	{
		MapChipDelete();
		m_pPlayer->BlowObstacle();
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
