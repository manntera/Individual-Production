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
	m_moveSpeed = 0.0f;
	m_acceleration = 0.0f;
	m_rotationCount = 0;
	m_rotationFrameNum = 3;
	m_frameAngle = 0.0f;
}

Player::~Player()
{

}

void Player::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
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
	m_characterController.SetGravity(-40.0f);
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_characterController.Init(2.0f, 2.5f, m_position);
	m_skinModel.SetShadowCasterFlg(true);
	//m_skinModel.SetShadowReceiverFlg(true);
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
	m_graspCliff.Init(this, 6.0f);
	m_wallJump.Init(this, &m_characterController);
	m_isParentRotation = false;
}


void Player::Update()
{
	if (g_gameScene == nullptr )
	{
		return;
	}
	Move();
	//m_graspCliff.Update();
	m_wallJump.Update();
	m_anim.Update(GetGameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, m_scale);
	if (m_characterController.IsOnGround())
	{
		DelayRotation(m_characterController.GetMoveSpeed());
	}
	if (m_position.y < -70.0f)
	{
		g_gameScene->GameOver();
	}

	if (GetPad().IsTriggerButton(enButtonY))
	{
		//SoundSource* sound = New<SoundSource>(0);
		//sound->Init("Assets/sound/univ1197a.wav", true);
		//sound->Play(false);
		//sound->SetPosition(m_position);
		//ParticleEmitter* emitter = New<ParticleEmitter>(0);
		//emitter->Init({
		//	"Assets/particle/Explosion5.png",
		//	10.0f,
		//	10.0f,
		//	{ 0.5f, 0.0f, 0.666f, 0.166f },
		//	1.0f,
		//	0.3f,
		//	3.0f,
		//	m_position
		//}
		//, &g_gameScene->GetCamera());
	}
	if (GetPad().IsTriggerButton(enButtonX))
	{
		//g_gameScene->GameOver();
	}
	GetShadowMap().SetLightCameraTarget(m_characterController.GetPosition());
	D3DXVECTOR3 lightCameraPos = m_characterController.GetPosition();
	lightCameraPos += {0.0f, 40.0f, 0.0f};
	GetShadowMap().SetLightCameraPosition(lightCameraPos);
}

void Player::CliffRiseStart(D3DXVECTOR3 moveDirection)
{
	//崖を上るアニメーションを再生
	m_anim.PlayAnimation(enAnimSetCliffRise);
	moveDirection.y = 0.0f;
	Rotation(moveDirection);
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

void Player::WallShear(D3DXVECTOR3 playerDirection)
{
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_currentAnim = enAnimSetWallShear;
	m_anim.PlayAnimation(enAnimSetWallShear);
	Rotation(playerDirection);
}


void Player::WallJump(D3DXVECTOR3 jumpDirection)
{
	D3DXVECTOR3 jumpSpeed = jumpDirection;
	jumpSpeed.y = 0.0f;
	D3DXVec3Normalize(&jumpSpeed, &jumpSpeed);
	jumpSpeed *= 25.0f;
	jumpSpeed.y = 30.0f;
	m_characterController.SetMoveSpeed(jumpSpeed);
	Rotation(jumpSpeed);
	m_jumpCount = 1;
	m_currentAnim = enAnimSetWallJump;
	m_anim.PlayAnimation(enAnimSetWallJump);
	SoundSource* sound = New<SoundSource>(0);
	sound->Init("Assets/sound/univ0001.wav");
	sound->Play(false);
	sound->SetVolume(0.8f);
	sound = New<SoundSource>(0);
	sound->Init("Assets/sound/Jump.wav");
	sound->Play(false);
	sound->SetVolume(0.3f);
}

void Player::SetParent(MapChip* parent, bool parentRotation)
{
	m_parent = parent;
	if (parent != nullptr)
	{
		D3DXMATRIX matrix = m_parent->GetWorldMatrix();
		D3DXMatrixInverse(&matrix, NULL, &matrix);
		D3DXVec3TransformCoord(&m_localPosition, &m_position, &matrix);
		m_isParentRotation = parentRotation;
		if (m_isParentRotation)
		{
			D3DXQUATERNION multi;
			D3DXQuaternionRotationMatrix(&multi, &matrix);
			D3DXQuaternionMultiply(&m_localRotation, &m_rotation, &multi);
		}
	}
}


void Player::Move()
{
	D3DXVECTOR3 moveSpeed = m_characterController.GetMoveSpeed();
	if (m_characterController.IsOnGround())
	{
		m_jumpCount = 0;
		m_isJump = false;
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

	D3DXVECTOR3 stickDir = -side * GetPad().GetLeftStickX();
	stickDir += front * GetPad().GetLeftStickY();

	const float acceleration = 0.1f;
	const float speedLimit = 20.0f;
	if (stickDir.x == 0.0f && stickDir.z == 0.0f)
	{
		if (m_characterController.IsOnGround() && m_currentAnim != enAnimSetWait)
		{
			m_currentAnim = enAnimSetWait;
			m_anim.PlayAnimation(enAnimSetWait);
		}
		m_acceleration = 0.0f;
		m_moveSpeed = 0.0f;
	}
	else
	{

		m_acceleration += acceleration;
		m_moveSpeed += m_acceleration;
		float speed = m_moveSpeed;
		if (speedLimit < speed)
		{
			speed = speedLimit;
		}
		if (!m_wallJump.IsWallShear() && !m_graspCliff.IsActive())
		{

			if (m_characterController.IsOnGround())
			{
				if (m_currentAnim != enAnimSetRun)
				{
					m_currentAnim = enAnimSetRun;
					m_anim.PlayAnimation(enAnimSetRun);
				}
				moveSpeed += stickDir;
				moveSpeed *= speed;
			}
			else
			{

				D3DXVECTOR3 jumpSpeed = stickDir;
				speed *= 0.05f;
				jumpSpeed *= speed;
				moveSpeed += jumpSpeed;
				D3DXVECTOR3 moveDirection = moveSpeed;
				moveDirection.y = 0.0f;
				if (speedLimit < D3DXVec3Length(&moveDirection))
				{
					D3DXVec3Normalize(&moveDirection, &moveDirection);
					moveSpeed.x = moveDirection.x * speedLimit;
					moveSpeed.z = moveDirection.z * speedLimit;
				}
			}
		}
		else
		{
			m_acceleration = 0.0f;
			m_moveSpeed = 0.0f;
		}
	}
	

	if (!m_characterController.IsOnGround() && !m_isJump)
	{
		m_isJump = true;
		m_jumpCount = 1;
	}
	if (GetPad().IsTriggerButton(enButtonA) && m_jumpCount < 2 && !m_wallJump.IsWallShear() && !m_graspCliff.IsActive())
	{

		if (m_jumpCount != 0)
		{
			D3DXVECTOR3 jumpDir = stickDir;
			D3DXVec3Normalize(&jumpDir, &jumpDir);
			jumpDir *= D3DXVec3Length(&moveSpeed);
			moveSpeed = jumpDir;
		}
		else
		{
			SoundSource* jumpSound;
			jumpSound = New<SoundSource>(0);
			jumpSound->Init("Assets/sound/Jump.wav");
			jumpSound->Play(false);
			jumpSound->SetVolume(0.3f);

		}
		moveSpeed.y = 30.0f;
		m_currentAnim = enAnimSetJump;
		m_anim.PlayAnimation(enAnimSetJump);
		Rotation(moveSpeed);
		SoundSource* sound = New<SoundSource>(0);
		sound->Init("Assets/sound/univ0002.wav");
		sound->Play(false);
		sound->SetVolume(0.8f);
		m_jumpCount++;

	}

	if (m_wallJump.IsWallShear())
	{
		moveSpeed = { 0.0f, 0.0f, 0.0f };
		m_position.y -= 0.2f;
		m_characterController.SetPosition(m_position);
	}

	moveSpeed += m_stageGimmickMoveSpeed;
	m_characterController.SetMoveSpeed(moveSpeed);
	if (m_parent != nullptr)
	{
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &m_localPosition, &m_parent->GetWorldMatrix());
		m_characterController.SetPosition(position);
		if (!m_graspCliff.IsActive() && !m_wallJump.IsWallShear())
		{
			m_characterController.Execute();
		}
		position = m_characterController.GetPosition();
		D3DXMATRIX inverseMatrix;
		D3DXMatrixInverse(&inverseMatrix, NULL, &m_parent->GetWorldMatrix());
		D3DXVec3TransformCoord(&m_localPosition, &position, &inverseMatrix);
	}
	else
	{
		if (!m_graspCliff.IsActive() && !m_wallJump.IsWallShear())
		{
			m_characterController.Execute();
		}
	}

	m_movement = m_characterController.GetPosition() - m_position;
	m_position = m_characterController.GetPosition();
	m_stageGimmickMoveSpeed = { 0.0f, 0.0f, 0.0f };
}

void Player::SetStageGimmickMoveSpeed(D3DXVECTOR3 moveSpeed)
{
	m_stageGimmickMoveSpeed += moveSpeed / GetGameTime().GetDeltaFrameTime();
}

void Player::DelayRotation(D3DXVECTOR3 rotationDirection)
{
	D3DXVECTOR3 moveDir = rotationDirection;
	moveDir.y = 0.0f;

	D3DXQUATERNION multi;
	D3DXQuaternionIdentity(&multi);
	//モデルを回転
	if (0.0f < D3DXVec3Length(&moveDir))
	{
		m_rotationCount = 0;
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
		m_frameAngle = rad / m_rotationFrameNum;
	}
	if (m_rotationCount < m_rotationFrameNum)
	{
		D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_frameAngle);
		m_rotationCount++;
	}

	if (m_parent != nullptr && m_isParentRotation)
	{
		D3DXQuaternionMultiply(&m_localRotation, &m_localRotation, &multi);
		D3DXQuaternionRotationMatrix(&multi, &m_parent->GetWorldMatrix());
		D3DXQuaternionMultiply(&m_rotation, &m_localRotation, &multi);
	}
	else
	{
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	}
}

void Player::Rotation(D3DXVECTOR3 rotationDirection)
{
	D3DXVECTOR3 moveDir = rotationDirection;
	moveDir.y = 0.0f;
	if (D3DXVec3Length(&moveDir) < 0.001f)
	{
		return;
	}
	D3DXQUATERNION multi;
	D3DXQuaternionIdentity(&multi);
	//モデルを回転
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

	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
	if (m_parent != nullptr && m_isParentRotation)
	{
		D3DXQuaternionMultiply(&m_localRotation, &m_localRotation, &multi);
		D3DXQuaternionRotationMatrix(&multi, &m_parent->GetWorldMatrix());
		D3DXQuaternionMultiply(&m_rotation, &m_localRotation, &multi);
	}
	else
	{
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &multi);
	}
}


void Player::Draw()
{
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	DWORD zStateBackup;
	DWORD zEnableStateBackup;
	DWORD zwriteEnableStateBackup;

	EnSkinModelShaderTechnique techniqueBackup = m_skinModel.GetCurrentShaderTechnique();
	device->GetRenderState(D3DRS_ZFUNC, &zStateBackup);
	device->GetRenderState(D3DRS_ZENABLE, &zEnableStateBackup);
	device->GetRenderState(D3DRS_ZWRITEENABLE, &zwriteEnableStateBackup);

	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	m_skinModel.SetShaderTechnique(enShaderTechniqueSilhouette);

	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());

	m_skinModel.SetShaderTechnique(techniqueBackup);
	device->SetRenderState(D3DRS_ZFUNC, zStateBackup);
	device->SetRenderState(D3DRS_ZENABLE, zEnableStateBackup);
	device->SetRenderState(D3DRS_ZWRITEENABLE, zwriteEnableStateBackup);

	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());
	m_characterController.Draw();
	m_wallJump.Draw();
	m_graspCliff.Draw();

}
