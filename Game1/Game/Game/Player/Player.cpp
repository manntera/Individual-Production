#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"
#include  "../Scene/Fade.h"
#include "../Map/MapChip/MoveFloor.h"
#include "../Map/MapChip/MapChip.h"

Player::Player()
{
	m_jumpCount = 0;
	m_stageGimmickMoveSpeed = { 0.0f, 0.0f, 0.0f };
	m_isJump = false;
	m_currentAnim = enAnimSetWait;
	m_movement = { 0.0f, 0.0f, 0.0f };
	m_parent = nullptr;
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
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_characterController.SetGravity(-90.0f);
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_characterController.Init(2.0f, 1.0f, m_position);
	m_graspCliff.Init(this, 6.0f);
	m_wallJump.Init(this, &m_characterController);
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
	m_wallJump.Update();
	m_anim.Update(1.0f / 60.0f);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (m_graspCliff.IsActive())
	{
		return;
	}
	Move();
	Jump();
	if (m_characterController.IsOnGround())
	{
		Rotation();
	}
	if (m_position.y < -10.0f)
	{
		//g_gameScene->GameOver();
	}
	if (GetPad().IsTriggerButton(enButtonY))
	{
		//m_anim.PlayAnimation(enAnimSetCliffRise);
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/reload.wav");
		//sound->Init("Assets/sound/BattleScene.wav");
		sound->Play(false);
	}
	if (GetPad().IsTriggerButton(enButtonX))
	{
		g_gameScene->GameOver();
	}
}

void Player::CliffRiseStart(D3DXVECTOR3 moveDirection)
{
	//崖を上るアニメーションを再生
	m_anim.PlayAnimation(enAnimSetCliffRise);
	moveDirection.y = 0.0f;
	m_characterController.SetMoveSpeed(moveDirection);
	Rotation();
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
}

bool Player::CriffRiseEnd()
{
	//崖を上ってない時か崖を上っている途中の場合早期リターンする
	if (m_anim.IsPlay())
	{
		return false;
	}
	//崖を上り終わって座標を更新
	D3DXMATRIX* matrix = m_skinModelData.GetFindBoneWorldMatrix("Character1_Reference");
	m_position.x = matrix->m[3][0];
	m_position.y = matrix->m[3][1];
	m_position.z = matrix->m[3][2];
	m_characterController.SetPosition(m_position);
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
	m_anim.PlayAnimation(enAnimSetWait);
	m_currentAnim = enAnimSetWait;
	return true;
}

void Player::WallShear(D3DXVECTOR3 moveSpeed)
{
	m_characterController.SetMoveSpeed(moveSpeed);
	m_currentAnim = enAnimSetWallShear;
	m_anim.PlayAnimation(enAnimSetWallShear);
	Rotation();
}

void Player::WallJump(D3DXVECTOR3 jumpDirection)
{
	D3DXVECTOR3 jumpSpeed = jumpDirection;
	jumpSpeed.y = 0.0f;
	D3DXVec3Normalize(&jumpSpeed, &jumpSpeed);
	jumpSpeed *= 25.0f;
	jumpSpeed.y = 50.0f;
	m_characterController.SetMoveSpeed(jumpSpeed);
	Rotation();
	m_jumpCount = 1;
	m_currentAnim = enAnimSetWallJump;
	m_anim.PlayAnimation(enAnimSetWallJump);
}

void Player::SetParent(MapChip* parent)
{
	m_parent = parent;
	if (parent != nullptr)
	{
		D3DXMATRIX matrix = m_parent->GetWorldMatrix();
		D3DXMatrixInverse(&matrix, NULL, &matrix);
		D3DXVec3TransformCoord(&m_localPosition, &m_position, &matrix);
		D3DXQUATERNION multi;
		D3DXQuaternionRotationMatrix(&multi, &matrix);
		D3DXQuaternionMultiply(&m_localRotation, &m_rotation, &multi);
	}
}


void Player::Move()
{
	//移動
	D3DXVECTOR3 moveSpeed = {0.0f, 0.0f, 0.0f};
	moveSpeed = m_characterController.GetMoveSpeed();
	if (m_characterController.IsOnGround())
	{
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
	}
	Camera& camera = g_gameScene->GetCamera();
	//カメラの向きを移動方向として移動
	D3DXVECTOR3 front = camera.GetTarget() - camera.GetPosition();
	front.y = 0.0f;
	D3DXVec3Normalize(&front, &front);
	D3DXVECTOR3 side;
	//横への移動方向は外積を取って求める
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
	if (!m_wallJump.IsWallJump())
	{
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
	}
	if (GetPad().IsTriggerButton(enButtonA) && m_jumpCount < 2 && !m_wallJump.IsWallJump())
	{
		moveSpeed.y = 0.0f;
		if (m_jumpCount != 0)
		{

			moveSpeed.x = (moveDirectionSide.x + moveDirectionFront.x) * speedLimit;
			moveSpeed.z = (moveDirectionSide.z + moveDirectionFront.z) * speedLimit;
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
	if (m_wallJump.IsWallShear())
	{
		moveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	if (m_parent != nullptr)
	{
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &m_localPosition, &m_parent->GetWorldMatrix());
		m_characterController.SetPosition(position);
		m_characterController.SetMoveSpeed(moveSpeed);
		m_characterController.Execute();
		position = m_characterController.GetPosition();
		D3DXMATRIX inverseMatrix;
		D3DXMatrixInverse(&inverseMatrix, NULL, &m_parent->GetWorldMatrix());
		D3DXVec3TransformCoord(&m_localPosition, &position, &inverseMatrix);
	}
	else
	{
		m_characterController.SetMoveSpeed(moveSpeed);
		m_characterController.Execute();
	}

	m_movement = m_characterController.GetPosition() - m_position;
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
	//モデルを回転
	if (0.0f < D3DXVec3Length(&moveDir))
	{
		D3DXMATRIX worldMat = m_skinModel.GetWorldMatrix();
		D3DXVECTOR3 front;

		front.x = worldMat.m[2][0];
		front.y = 0.0f;
		front.z = worldMat.m[2][2];
		D3DXVec3Normalize(&moveDir, &moveDir);
		D3DXVec3Normalize(&front, &front);

		float rad = D3DXVec3Dot(&front, &moveDir);
		if (1.0f < rad)
		{
			rad = 1.0f;
		}
		if (rad < -1.0f)
		{
			rad = 1.0f;
		}
		rad = acosf(rad);
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &front, &moveDir);
		if (cross.y < 0.0f)
		{
			rad = -rad;
		}

		if (m_parent != nullptr)
		{
			D3DXQUATERNION multi;
			D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
			D3DXQuaternionMultiply(&m_localRotation, &m_localRotation, &multi);
			D3DXQuaternionRotationMatrix(&multi, &m_parent->GetWorldMatrix());
			D3DXQuaternionMultiply(&m_rotation, &m_localRotation, &multi);

		}
		else
		{
			D3DXQUATERNION multi;
			D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
			D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
		}
	}
	else
	{
		if (m_parent != nullptr)
		{
			D3DXQUATERNION multi;
			D3DXQuaternionRotationMatrix(&multi, &m_parent->GetWorldMatrix());
			D3DXQuaternionMultiply(&m_rotation, &m_localRotation, &multi);

		}
	}
}


void Player::Draw()
{
	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());
}
