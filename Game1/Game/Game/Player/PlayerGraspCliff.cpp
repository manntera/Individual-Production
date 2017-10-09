#include "stdafx.h"
#include "PlayerGraspCliff.h"
#include "Player.h"

void PlayerGraspCliff::Init(Player* player, float height)
{
	m_player = player;
	m_playerHeight = height;
	D3DXVECTOR3 position  = m_player->GetPosition();
	D3DXMATRIX matrix = m_player->GetWorldMatrix();
	D3DXQUATERNION rotation;
	D3DXQuaternionRotationMatrix(&rotation, &matrix);
	m_boxColliderLow.Create({ 10.0f, 0.1f, 10.2f });
	m_boxColliderUp.Create({ 1.0f, 0.1f, 2.2f });
	position.y += m_playerHeight;
	m_cliffRiseDetectionLow.Init(&m_boxColliderLow, position, rotation);
	position.y += 0.2f;
	m_cliffRiseDetectionUp.Init(&m_boxColliderUp, position, rotation);
	m_cliffRiseDetectionLow.SetUserIndex(enCollisionAttr_CliffDetection);
	m_cliffRiseDetectionUp.SetUserIndex(enCollisionAttr_CliffDetection);
}

void PlayerGraspCliff::Update()
{
	D3DXVECTOR3 position = m_player->GetPosition();
	position.y += m_playerHeight;
	m_cliffRiseDetectionLow.SetPosition(position);
	position.y += 1.0f;
	m_cliffRiseDetectionUp.SetPosition(position);

	D3DXMATRIX matrix = m_player->GetWorldMatrix();
	D3DXQUATERNION rotation;
	D3DXQuaternionRotationMatrix(&rotation, &matrix);
	m_cliffRiseDetectionLow.SetRotation(rotation);
	m_cliffRiseDetectionUp.SetRotation(rotation);

	m_cliffRiseDetectionLow.Execute();
	m_cliffRiseDetectionUp.Execute();
	if (m_cliffRiseDetectionLow.IsHit()&&/*
		!m_cliffRiseDetectionUp.IsHit() &&*/
		m_player->IsActive())
	{
		m_player->SetActiveFlg(false);
		m_player->PlayAnimation(enAnimSetCliffRise);
	}
	if (!m_player->IsActive() && !m_player->IsPlay())
	{
		m_player->SetActiveFlg(true);
		m_player->CriffRise();
	}
}

void PlayerGraspCliff::Draw()
{
	m_cliffRiseDetectionLow.Draw();
	m_cliffRiseDetectionUp.Draw();
}