#include "stdafx.h"
#include "PlayerWallJump.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"

PlayerWallJump::PlayerWallJump()
{
	m_isWallShear = false;
	m_player = nullptr;
	m_characterController = nullptr;
	m_wallJumpDirection = { 0.0f, 0.0f, 0.0f };
	m_isWallJump = false;
	m_wallDust = nullptr;
	m_wallShearGravity = -200.0f;
}

PlayerWallJump::~PlayerWallJump()
{

}


void PlayerWallJump::Init(Player* player, CharacterController* characterController)
{
	m_player = player;
	m_characterController = characterController;
	m_boxCollider.Create({ 0.1f, 0.1f, 0.1f });
	D3DXVECTOR3 position = m_player->GetPosition();
	D3DXMATRIX worldMatrix = m_player->GetWorldMatrix();
	D3DXVECTOR3 playerFront;
	playerFront.x = worldMatrix.m[2][0];
	playerFront.y = worldMatrix.m[2][1];
	playerFront.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&playerFront, &playerFront);
	playerFront *= 1.3f;
	position += playerFront;
	D3DXQUATERNION rotation;
	D3DXQuaternionRotationMatrix(&rotation, &worldMatrix);
	m_wallDetection.Init(&m_boxCollider, position, rotation);

	m_defaultGravity = m_characterController->GetGravity();
	m_dustPos = m_player->FindBoneWorldMatrix("Character1_RightToeBase");
}

void PlayerWallJump::Update()
{
	m_isWallJump = false;
	m_wallDetection.Execute();
	if (!m_isWallShear)
	{
		D3DXVECTOR3 movement = m_player->GetMovement();
		movement.y = 0.0f;
		m_characterController->SetGravity(m_defaultGravity);

		if (m_characterController->IsJump() && 
			m_characterController->GetWallCollisionObject() != nullptr &&
			0.12f < D3DXVec3Length(&movement))
		{
			D3DXVECTOR3 wallNormal = m_characterController->GetWallNormal();
			wallNormal.y = 0.0f;
			D3DXVec3Normalize(&wallNormal, &wallNormal);
			D3DXVECTOR3 playerDirection = m_characterController->GetMoveSpeed();
			playerDirection.y = 0.0f;
			D3DXVec3Normalize(&playerDirection, &playerDirection);				
			playerDirection *= -1.0f;
			float dot = D3DXVec3Dot(&playerDirection, &wallNormal);
			float rad = 30.0f / 180.0f * cPI;
			if (sin(rad) < dot)
			{
				m_isWallShear = true;
				playerDirection *= -1.0f;
				wallNormal *= dot * 2.0f;
				playerDirection += wallNormal;
				m_wallJumpDirection = playerDirection;
				D3DXVec3Normalize(&m_wallJumpDirection, &m_wallJumpDirection);
				m_player->WallShear(-wallNormal);
				D3DXVECTOR3 position;
				position.x = m_dustPos->m[3][0];
				position.y = m_dustPos->m[3][1];
				position.z = m_dustPos->m[3][2];
				m_wallDust = New<ParticleEmitter>(cameraPriority);
				m_wallDust->Init({
					"Assets/particle/WallDust.png",		//テクスチャのファイルパス
					2.0f,								//パーティクルの横幅
					2.0f,								//パーティクルの縦幅
					{ 0.0f, 0.0f, 1.0f, 1.0f },			//テクスチャのuv。xyが左上のuvでzwが右下のuv
					0.7f,								//パーティクルの寿命
					0.4f,								//パーティクルが出るまでのインターバル
					0.0f,								//エミッターの寿命
					position							//エミッターの座標
				}
				, &g_gameScene->GetCamera());
			}
		}
	}
	else
	{

		m_characterController->SetGravity(m_wallShearGravity);
		D3DXVECTOR3 position = m_player->GetPosition();
		D3DXMATRIX worldMatrix = m_player->GetWorldMatrix();
		D3DXVECTOR3 playerFront;
		playerFront.x = worldMatrix.m[2][0];
		playerFront.y = worldMatrix.m[2][1];
		playerFront.z = worldMatrix.m[2][2];
		D3DXVec3Normalize(&playerFront, &playerFront);
		playerFront *= 2.9f;
		position += playerFront;
		D3DXQUATERNION rotation;
		D3DXQuaternionRotationMatrix(&rotation, &worldMatrix);
		m_wallDetection.SetPosition(position);
		m_wallDetection.SetRotation(rotation);
		m_wallDetection.Execute();
		m_isWallShear = m_wallDetection.IsHit();

		position.x = m_dustPos->m[3][0];
		position.y = m_dustPos->m[3][1];
		position.z = m_dustPos->m[3][2];
		m_wallDust->SetPosition(position);
		if (GetPad().IsTriggerButton(enButtonA))
		{
			m_characterController->SetGravity(m_defaultGravity);
			m_player->WallJump(m_wallJumpDirection);
			m_isWallShear = false;
			m_isWallJump = true;
			Delete(m_wallDust);
			m_wallDust = nullptr;
		}

		if (m_wallDust != nullptr && !m_isWallShear)
		{
			Delete(m_wallDust);
			m_wallDust = nullptr;

		}

	}
}
