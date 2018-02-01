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
	m_wallJumpCount = 0;
}

PlayerWallJump::~PlayerWallJump()
{

}


void PlayerWallJump::Init(Player* player, CharacterController* characterController)
{
	m_player = player;
	m_characterController = characterController;

	m_groundCollider.Create({ 0.3f, 0.3f, 0.3f });
	m_wallCollider.Create({ 1.0f, 0.3f, 0.05f });
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
	m_wallDetection.Init(&m_wallCollider, position, rotation);
	m_wallDetection.SetJudgmentType(enJudgment_Inactive);
	position = m_player->GetPosition();
	m_groundDetection.Init(&m_groundCollider, position, rotation);
	m_groundDetection.SetJudgmentType(enJudgment_Ground);
	m_defaultGravity = m_characterController->GetGravity();
	m_dustPos = m_player->FindBoneWorldMatrix("Character1_RightToeBase");
}

void PlayerWallJump::Update()
{
	if (m_isWallJump)
	{
		m_wallJumpCount++;
		if (3 <= m_wallJumpCount)
		{
			m_isWallJump = false;
			m_wallJumpCount = 0;
		}
		return;
	}
	D3DXVECTOR3 position = m_player->GetPosition();
	D3DXMATRIX worldMatrix = m_player->GetWorldMatrix();
	D3DXVECTOR3 playerFront;
	playerFront.x = worldMatrix.m[2][0];
	playerFront.y = worldMatrix.m[2][1];
	playerFront.z = worldMatrix.m[2][2];
	D3DXVec3Normalize(&playerFront, &playerFront);
	playerFront *= 2.0f;
	position += playerFront;
	D3DXQUATERNION rotation;
	D3DXQuaternionRotationMatrix(&rotation, &worldMatrix);
	position.y += 3.0f;
	m_wallDetection.SetPosition(position);
	m_wallDetection.SetRotation(rotation);
	position = m_player->GetPosition();
	position.y -= 0.2f;
	m_groundDetection.SetPosition(position);
	m_groundDetection.SetRotation(rotation);
	GetPhysicsWorld().Update();
	m_groundDetection.Execute();
	m_wallDetection.Execute();
	//壁に張り付いてない時
	if (!m_isWallShear)
	{
		D3DXVECTOR3 movement = m_player->GetMovement();
		movement.y = 0.0f;

		//ジャンプ中で壁に当たって移動速度がある程度あるとき
		if (m_characterController->IsJump() && 
			m_wallDetection.IsHit()/* &&
			0.12f < D3DXVec3Length(&movement)*/)
		{
			//壁の法線とプレイヤーの向きで内積を計算
			D3DXVECTOR3 wallNormal = m_wallDetection.GetCollisionNormal();
			wallNormal.y = 0.0f;
			D3DXVec3Normalize(&wallNormal, &wallNormal);
			D3DXMATRIX matrix = m_player->GetWorldMatrix();
			D3DXVECTOR3 playerDirection;
			playerDirection.x = matrix.m[2][0];
			playerDirection.y = 0.0f;
			playerDirection.z = matrix.m[2][2];
			D3DXVec3Normalize(&playerDirection, &playerDirection);				
			playerDirection *= -1.0f;
			float dot = D3DXVec3Dot(&playerDirection, &wallNormal);
			float rad = 30.0f / 180.0f * cPI;
			//壁に対して入射角がある程度あった場合壁に張り付く
			//if (sin(rad) < dot)
			{
				m_wallDetection.SetJudgmentType(enJudgment_Wall);
				m_isWallShear = true;
				m_characterController->SetGravity(m_wallShearGravity);
				playerDirection *= -1.0f;
				wallNormal *= dot * 2.0f;
				playerDirection += wallNormal;
				m_wallJumpDirection = playerDirection;
				D3DXVec3Normalize(&m_wallJumpDirection, &m_wallJumpDirection);
				m_player->WallShear(-wallNormal);
				position.x = m_dustPos->m[3][0];
				position.y = m_dustPos->m[3][1];
				position.z = m_dustPos->m[3][2];
				m_wallDust = New<ParticleEmitter>(CAMERA_PRIORITY);
				m_wallDust->Init({
					"Assets/particle/WallDust.png",		//テクスチャのファイルパス
					2.0f,								//パーティクルの横幅
					2.0f,								//パーティクルの縦幅
					{ 0.0f, 0.0f, 1.0f, 1.0f },			//テクスチャのuv。xyが左上のuvでzwが右下のuv
					{ 0.0f, 0.0f, 0.0f },				//パーティクルの座標のランダム幅
					{ 0.0f, 0.0f, 0.0f },				//パーティクルの重力
					0.7f,								//パーティクルの寿命
					0.4f,								//パーティクルが出るまでのインターバル
					0.0f,								//エミッターの寿命
					position,							//エミッターの座標
					1									//パーティクルが1フレームで出る数
				}
				, &g_gameScene->GetCamera());
			}
		}
	}
	else//壁に張り付いてる時
	{

		position.x = m_dustPos->m[3][0];
		position.y = m_dustPos->m[3][1];
		position.z = m_dustPos->m[3][2];
		m_wallDust->SetPosition(position);
		m_isWallShear = m_wallDetection.IsHit();
		if (GetPad().IsTriggerButton(enButtonA))
		{
			m_player->WallJump(m_wallJumpDirection);
			m_isWallShear = false;
			m_isWallJump = true;
		}
		if (m_wallDust != nullptr && m_isWallShear &&
			m_groundDetection.IsHit() &&
			m_groundDetection.GetHitCollisionType() != enCollisionAttr_Character)
		{
			m_isWallShear = false;
		}

		if (m_wallDust != nullptr && !m_isWallShear)
		{
			Delete(m_wallDust);
			m_wallDust = nullptr;
			m_characterController->SetGravity(m_defaultGravity);
			m_wallDetection.SetJudgmentType(enJudgment_Inactive);

		}
	}
}


void PlayerWallJump::Draw()
{
	const int detectionNum = 2;
	CollisionDetection* detection[detectionNum] =
	{
		&m_groundDetection,
		&m_wallDetection,
	};
	BoxCollider* collider[detectionNum] = 
	{
		&m_groundCollider,
		&m_wallCollider,
	};
	for (int i = 0; i < detectionNum; i++)
	{
		//剛体を描画
		D3DXVECTOR3 position = detection[i]->GetPosition();
		D3DXQUATERNION rotation = detection[i]->GetRotation();
		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

		GetPhysicsWorld().DebugDraw(trans, collider[i]->GetBody());
	}
}