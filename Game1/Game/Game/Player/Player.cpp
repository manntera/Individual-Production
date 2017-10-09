#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"
#include  "../Scene/Fade.h"
#include "../Map/MapChip/MoveFloor.h"

Player::Player()
{
	m_jumpCount = 0;
	m_stageGimmickMoveSpeed = { 0.0f, 0.0f, 0.0f };
	m_isWallShear = false;
	m_isJump = false;
	m_wallShearGravity = -60.0f;
	m_defaultGravity = -90.0f;
	m_wallJumpDirection = { 0.0f, 0.0f, 0.0f };
	m_currentAnim = enAnimSetWait;
	m_isActive = true;
}

Player::~Player()
{

}

void Player::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	//float ambient = 0.6f;
	//float diffuseColor = 0.3f;
	//m_light.SetAmbiemtLight({ ambient, ambient, ambient, 1.0f });
	//m_light.SetDiffuseLightColor(0, { diffuseColor, diffuseColor, diffuseColor, 1.0f });
	//m_light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, 0.707f, 1.0f });

	float ambientLightColor = 0.6f;
	float diffuseLightColor0 = 0.3f;
	float diffuseLightColor1 = 0.3f;
	float diffuseLightColor2 = 0.2f;
	float diffuseLightColor3 = 0.15f;
	m_light.SetAmbiemtLight({ ambientLightColor, ambientLightColor, ambientLightColor, 1.0f });
	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(diffuseLightColor0, diffuseLightColor0, diffuseLightColor0, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(diffuseLightColor1, diffuseLightColor1, diffuseLightColor1, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(diffuseLightColor2, diffuseLightColor2, diffuseLightColor2, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(diffuseLightColor3, diffuseLightColor3, diffuseLightColor3, 1.0f));
	D3DXVECTOR3 lightDirection;
	lightDirection = { -7.0f, -4.5f, -5.0f };
	D3DXVec3Normalize(&lightDirection, &lightDirection);
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));
	lightDirection = { 2.0f, 0.0f, 10.0f };
	D3DXVec3Normalize(&lightDirection, &lightDirection);
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));
	lightDirection = { 10.0f, -3.0f, -4.0f };
	D3DXVec3Normalize(&lightDirection, &lightDirection);
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));
	lightDirection = { -5.0f, -5.0f, 5.0f };
	D3DXVec3Normalize(&lightDirection, &lightDirection);
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(lightDirection.x, lightDirection.y, lightDirection.z, 1.0f));

	m_rotation = rotation;
	m_position = position;
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_characterController.Init(1.0f, 1.0f, m_position);
	m_graspCliff.Init(this, 2.5f);
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_characterController.SetGravity(-90.0f);
	m_skinModel.SetShadowCasterFlg(true);
	m_skinModel.SetShadowReceiverFlg(true);

}

void Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/Unitychan.X", &m_anim);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&m_light);
	m_modelNormalMap.Load("Assets/modelData/utc_normal.tga");
	m_modelSpecularMap.Load("Assets/modelData/utc_spec.tga");
	m_skinModel.SetNormalMap(&m_modelNormalMap);
	m_skinModel.SetSpecularMap(&m_modelSpecularMap, &g_gameScene->GetCamera());
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_anim.SetAnimationEndTime(enAnimSetRun, 0.8f);
	m_anim.SetAnimationEndTime(enAnimSetWallJump, 0.9f);
	m_anim.SetAnimationLoopFlg(enAnimSetWallJump, false);
	m_anim.SetAnimationEndTime(enAnimSetJump, 0.7f);
	m_anim.SetAnimationLoopFlg(enAnimSetJump, false);
	m_anim.SetAnimationLoopFlg(enAnimSetCliffRise, false);
	m_anim.PlayAnimation(enAnimSetWait);
}


void Player::Update()
{
	if (g_gameScene == nullptr )
	{
		return;
	}
	m_graspCliff.Update();
	m_anim.Update(1.0f / 60.0f);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (!m_isActive)
	{
		return;
	}
	Move();
	Jump();
	if (m_characterController.IsOnGround() && (GetPad().GetLeftStickX() != 0.0f || GetPad().GetLeftStickY() != 0.0f))
	{
		Rotation();
	}
	if (m_position.y < -10.0f)
	{
		g_gameScene->GameOver();
	}
}

void Player::CriffRise()
{
	D3DXMATRIX* matrix = m_skinModelData.GetFindBoneWorldMatrix("Character1_Reference");
	m_position.x = matrix->m[3][0];
	m_position.y = matrix->m[3][1];
	m_position.z = matrix->m[3][2];
	m_characterController.SetPosition(m_position);
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
}

void Player::Move()
{
	//ˆÚ“®
	D3DXVECTOR3 moveSpeed = {0.0f, 0.0f, 0.0f};
	moveSpeed = m_characterController.GetMoveSpeed();
	if (m_characterController.IsOnGround())
	{
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
	}
	Camera& camera = g_gameScene->GetCamera();
	//ƒJƒƒ‰‚ÌŒü‚«‚ğˆÚ“®•ûŒü‚Æ‚µ‚ÄˆÚ“®
	D3DXVECTOR3 front = camera.GetTarget() - camera.GetPosition();
	front.y = 0.0f;
	D3DXVec3Normalize(&front, &front);
	D3DXVECTOR3 side;
	//‰¡‚Ö‚ÌˆÚ“®•ûŒü‚ÍŠOÏ‚ğæ‚Á‚Ä‹‚ß‚é
	D3DXVec3Cross(&side, &front, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&side, &side);
	float speed = 25.0f;
	const float speedLimit = speed;
	if (!m_characterController.IsOnGround())
	{
		speed *= 0.01f;
	}
	D3DXVECTOR3 moveDirectionSide = -side * GetPad().GetLeftStickX();
	D3DXVECTOR3 moveDirectionFront = front * GetPad().GetLeftStickY();
	moveSpeed += moveDirectionSide * speed;
	moveSpeed += moveDirectionFront * speed;
	if (moveSpeed.x < -speedLimit)
	{
		moveSpeed.x = -speedLimit;
	}
	else if (speedLimit < moveSpeed.x)
	{
		moveSpeed.x = speedLimit;
	}
	if (moveSpeed.z < -speedLimit)
	{
		moveSpeed.z = -speedLimit;
	}
	else if (speedLimit < moveSpeed.z)
	{
		moveSpeed.z = speedLimit;
	}
	if (GetPad().IsTriggerButton(padButtonA) && m_jumpCount < 2)
	{
		moveSpeed.y = 0.0f;
		if (m_jumpCount != 0)
		{

			moveSpeed.x = (moveDirectionSide.x + moveDirectionFront.x) * speedLimit;
			moveSpeed.z = (moveDirectionSide.z + moveDirectionFront.z) * speedLimit;
			//moveSpeed.y += 15.0f * m_jumpCount;

		}
		moveSpeed.y += 50.0f;
		m_characterController.SetMoveSpeed(moveSpeed);
		Rotation();
		m_jumpCount++;
		//if (m_currentAnim != enAnimSetJump)
		//{
		//	m_currentAnim = enAnimSetJump;
		//	m_anim.PlayAnimation(enAnimSetJump);
		//}
		m_currentAnim = enAnimSetJump;
		m_anim.PlayAnimation(enAnimSetJump);
	}

	if (m_characterController.IsOnGround())
	{
		m_jumpCount = 0;
		m_isJump = false;
		if (moveSpeed.x == 0.0f && moveSpeed.z == 0.0f)
		{
			if (m_currentAnim != enAnimSetWait)
			{
				m_currentAnim = enAnimSetWait;
				m_anim.PlayAnimation(enAnimSetWait);
			}
		}
		else
		{
			if (m_currentAnim != enAnimSetRun)
			{
				m_currentAnim = enAnimSetRun;
				m_anim.PlayAnimation(enAnimSetRun);
			}
		}
	}
	else if(!m_isJump)
	{
		m_isJump = true;
		m_jumpCount = 1;
	}
	moveSpeed += m_stageGimmickMoveSpeed;
	if (0.0f < m_stageGimmickMoveSpeed.y)
	{
		m_currentAnim = enAnimSetJump;
		m_anim.PlayAnimation(enAnimSetJump);
		m_jumpCount = 1;
	}
	if (m_characterController.IsJump() )
	{

		//if (m_characterController.GetWallCollisionObject() != nullptr)
		//{
		//	
		//	//m_isWallShear = true;
		//	D3DXVECTOR3 wallNormal = m_characterController.GetWallNormal();
		//	wallNormal.y = 0.0f;
		//	D3DXVec3Normalize(&wallNormal, &wallNormal);
		//	D3DXVECTOR3 playerDirection = moveSpeed;
		//	playerDirection.y = 0.0f;
		//	D3DXVec3Normalize(&playerDirection, &playerDirection);
		//	playerDirection *= -1.0f;

		//	float dot = D3DXVec3Dot(&playerDirection, &wallNormal);
		//	if (0.0f < dot)
		//	{
		//		playerDirection *= -1.0f;
		//		wallNormal *= dot * 2.0f;
		//		playerDirection += wallNormal;
		//		m_wallJumpDirection = playerDirection;
		//		D3DXVec3Normalize(&m_wallJumpDirection, &m_wallJumpDirection);
		//		m_wallJumpDirection *= speedLimit;
		//		m_wallJumpDirection.y = 50.0f;
		//		if (m_currentAnim != enAnimSetWallShear)
		//		{
		//			m_currentAnim = enAnimSetWallShear;
		//			m_anim.PlayAnimation(enAnimSetWallShear);
		//		}
		//		m_characterController.SetMoveSpeed(-wallNormal);
		//		Rotation();
		//	}
		//}
	}
	else
	{
		m_isWallShear = false;
	}
	if (m_isWallShear)
	{
		moveSpeed = { 0.0f, 0.0f, 0.0f };
		m_characterController.SetGravity(m_wallShearGravity);
		if (GetPad().IsTriggerButton(padButtonA))
		{
			moveSpeed = m_wallJumpDirection;
			m_characterController.SetGravity(m_defaultGravity);
			m_characterController.SetMoveSpeed(moveSpeed);
			Rotation();
			m_jumpCount = 1;
			m_isWallShear = false;
			if (m_currentAnim != enAnimSetWallJump)
			{
				m_currentAnim = enAnimSetWallJump;
				m_anim.PlayAnimation(enAnimSetWallJump);
			}

		}
	}
	else
	{
		m_characterController.SetGravity(m_defaultGravity);
	}
	m_characterController.SetMoveSpeed(moveSpeed);
	m_characterController.Execute();
	m_position = m_characterController.GetPosition();
	m_stageGimmickMoveSpeed = { 0.0f, 0.0f, 0.0f };
}

void Player::Jump()
{

}

void Player::SetStageGimmickMoveSpeed(D3DXVECTOR3 moveSpeed)
{
	m_stageGimmickMoveSpeed += moveSpeed * 60.0f;
}

void Player::Rotation()
{
	D3DXVECTOR3 moveDir = m_characterController.GetMoveSpeed();
	moveDir.y = 0.0f;
	//ƒ‚ƒfƒ‹‚ğ‰ñ“]
	if (0.0f < D3DXVec3Length(&moveDir))
	{
		D3DXMATRIX worldMat = m_skinModel.GetWorldMatrix();
		D3DXVECTOR3 front;
		front.x = 0.0f;
		front.y = 0.0f;
		front.z = 1.0f;
		D3DXVec3Normalize(&moveDir, &moveDir);
		D3DXVec3Normalize(&front, &front);
		float rad = acos(D3DXVec3Dot(&front, &moveDir));
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &front, &moveDir);
		if (cross.y < 0.0f)
		{
			rad = -rad;
		}
		D3DXQUATERNION multi;
		D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
	}
}


void Player::Draw()
{
	m_graspCliff.Draw();
	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());
}
