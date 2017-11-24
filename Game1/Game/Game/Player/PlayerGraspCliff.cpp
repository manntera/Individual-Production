#include "stdafx.h"
#include "PlayerGraspCliff.h"
#include "Player.h"

PlayerGraspCliff::PlayerGraspCliff()
{
	m_isActive = false;
	m_playerHeight = 0.0f;
	m_player = nullptr;
}

PlayerGraspCliff::~PlayerGraspCliff()
{

}

void PlayerGraspCliff::Init(Player* player, float height)
{
	m_player = player;
	m_playerHeight = height;

	D3DXVECTOR3 position  = m_player->GetPosition();
	D3DXMATRIX matrix = m_player->GetWorldMatrix();
	D3DXQUATERNION rotation;
	D3DXQuaternionRotationMatrix(&rotation, &matrix);
	position.y += m_playerHeight;

	m_boxCollider.Create({ 1.0f, 0.1f, 0.1f });

	m_cliffRiseDetectionBack.Init(&m_boxCollider, position, rotation);
	m_cliffRiseDetectionLow.Init(&m_boxCollider, position, rotation);
	m_cliffRiseDetectionUp.Init(&m_boxCollider, position, rotation);

	m_cliffRiseDetectionLow.SetUserIndex(enCollisionAttr_CliffDetection);
	m_cliffRiseDetectionUp.SetUserIndex(enCollisionAttr_CliffDetection);
	m_cliffRiseDetectionBack.SetUserIndex(enCollisionAttr_CliffDetection);
}

void PlayerGraspCliff::Update()
{
	float m_upDifference = 0.4f;
	float m_backDifference = 1.0f;
	float m_frontDifference = 1.7f;

	//ÉèÅ[ÉãÉhçsóÒÇ©ÇÁâÒì]çsóÒÇà¯Ç¡í£Ç¡ÇƒÇ´ÇƒçÑëÃÇÃâÒì]Çê›íË
	D3DXMATRIX worldMatrix = m_player->GetWorldMatrix();
	D3DXQUATERNION rotation;
	D3DXQuaternionRotationMatrix(&rotation, &worldMatrix);
	m_cliffRiseDetectionLow.SetRotation(rotation);
	m_cliffRiseDetectionUp.SetRotation(rotation);

	//âÒì]çsóÒÇégÇ¡ÇƒçÑëÃÇÃà íuÇí≤êÆ
	D3DXVECTOR3 position = m_player->GetPosition();
	D3DXVECTOR3 playerFrontNormal;
	playerFrontNormal.x = worldMatrix.m[2][0];
	playerFrontNormal.y = 0.0f;
	playerFrontNormal.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&playerFrontNormal, &playerFrontNormal);
	position.y += m_playerHeight;
	position += playerFrontNormal * m_backDifference;
	m_cliffRiseDetectionBack.SetPosition(position);
	position += playerFrontNormal * m_frontDifference;
	m_cliffRiseDetectionLow.SetPosition(position);
	position.y += m_upDifference;
	m_cliffRiseDetectionUp.SetPosition(position);

	m_cliffRiseDetectionLow.Execute();
	m_cliffRiseDetectionUp.Execute();
	m_cliffRiseDetectionBack.Execute();

	//çÑëÃÇ™ìñÇΩÇ¡ÇƒÇ¢ÇƒäRÇè„Ç¡ÇƒÇ¢Ç»Ç¢éû
	if (m_cliffRiseDetectionLow.IsHit()&&
		!m_cliffRiseDetectionUp.IsHit() &&
		!m_cliffRiseDetectionBack.IsHit() &&
		!m_isActive)
	{
		D3DXVECTOR3 collisionNormal = m_cliffRiseDetectionLow.GetHitCOllisionNormal();
		D3DXVec3Normalize(&collisionNormal, &collisionNormal);
		if (D3DXVec3Dot(&playerFrontNormal, &collisionNormal) < 0.0f)
		{
			collisionNormal *= -1.0f;
		}
		m_player->CliffRiseStart(collisionNormal);
		m_isActive = true;
	}

	//äRÇè„Ç¡ÇƒÇ¢ÇÈéû
	if (m_isActive)
	{
		m_player->ParentChildMove();
		bool isActive = m_player->CriffRiseEnd();
		m_isActive = !isActive;
	}
}