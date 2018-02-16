#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"
#include  "../Scene/Fade.h"
#include "../Map/MapChip/MoveFloor.h"
#include "../Map/MapChip/MapChip.h"
#include "../GhostPlayer/GhostDataListManager.h"

Player::Player() :
	m_skinModel(),
	m_skinModelData(),
	m_light(),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_localRotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_localPosition(0.0f, 0.0f, 0.0f),
	m_scale(1.0f, 1.0f, 1.0f),
	m_anim(),
	m_characterController(),
	m_stageGimmickMoveSpeed(0.0f, 0.0f, 0.0f),
	m_movement(0.0f, 0.0f, 0.0f),
	m_wallJump(),
	m_jumpCount(0),
	m_currentAnim(enAnimSetWait),
	m_isJump(false),
	m_parent(nullptr),
	m_isParentRotation(false),
	m_moveSpeed(0.0f),
	m_acceleration(0.0f),
	m_rotationFrameNum(3),
	m_frameAngle(0.0f),
	m_rotationCount(0),
	m_jumpSpeed(27.0f)

{
}

Player::~Player()
{
}

void Player::GhostDataFinish(float time, bool isClear) const
{
	GetGhostDataListManager().Finish(time, isClear);
}

void Player::GhostDataStart() const
{
	GetGhostDataListManager().Start(&m_position, &m_rotation, &m_anim);
}


void Player::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	//���C�g�̐ݒ�
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

	//���[���h�s����X�V
	m_rotation = rotation;
	m_position = position;
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_skinModel.Update(m_position, m_rotation, m_scale);
	//�L�����N�^�[�R���g���[���[
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_characterController.SetGravity(-28.0f);
	m_characterController.Init(2.0f, 2.5f, m_position);
	m_skinModel.SetShadowCasterFlg(true);
	//m_skinModel.SetShadowReceiverFlg(true);
}

bool Player::Start()
{
	//���f���̏�����
	GetModelDataResource().Load(&m_skinModelData, &m_anim, "Assets/modelData/Unitychan.X");
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&m_light);
	//�@���}�b�v�ƃX�y�L�����}�b�v��ǂݍ���
	Texture* texture = GetTextureResource().LoadTexture("Assets/modelData/utc_normal.tga");
	m_skinModel.SetNormalMap(texture);
	texture = GetTextureResource().LoadTexture("Assets/modelData/utc_spec.tga");
	m_skinModel.SetSpecularMap(texture, &GetGameScene().GetCamera());

	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//�A�j���[�V�����̏�����
	m_anim.SetAnimationEndTime(enAnimSetRun, 0.8f);
	m_anim.SetAnimationEndTime(enAnimSetWallJump, 0.9f);
	m_anim.SetAnimationLoopFlg(enAnimSetWallJump, false);
	m_anim.SetAnimationEndTime(enAnimSetJump, 0.7f);
	m_anim.SetAnimationLoopFlg(enAnimSetJump, false);
	m_anim.SetAnimationLoopFlg(enAnimSetCliffRise, false);
	m_anim.SetAnimationLoopFlg(enAnimSetVerticalJump, false);
	

	m_wallJump.Init(this, &m_characterController);
	m_isParentRotation = false;
	return true;
}


void Player::Update()
{
	if (!GetGameScene().IsActive())
	{
		return;
	}
	Move();
	m_wallJump.Update();
	m_anim.Update(GetGameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, m_scale);
	if (m_characterController.IsOnGround())
	{
		//��]�����t���[�����ɕ������ĉ�]
		DelayRotation(m_characterController.GetMoveSpeed());
	}
	if (m_position.y < -70.0f)
	{
		GetGameScene().GameOver();
	}
	//�V���h�E�}�b�v�̃��C�g�J�������X�V
	GetShadowMap().SetLightCameraTarget(m_characterController.GetPosition());
	D3DXVECTOR3 lightCameraPos = m_characterController.GetPosition();
	lightCameraPos += {0.0f, 40.0f, 0.0f};
	GetShadowMap().SetLightCameraPosition(lightCameraPos);
}

void Player::CliffRiseStart(const D3DXVECTOR3& moveDirection)
{
	//�R�����A�j���[�V�������Đ�
	m_anim.PlayAnimation(enAnimSetCliffRise);
	D3DXVECTOR3 direction = moveDirection;
	direction.y = 0.0f;
	Rotation(direction);
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
}

bool Player::CriffRiseEnd()
{
	//�R������ĂȂ������R������Ă���r���̏ꍇ�������^�[������
	if (m_anim.IsPlay())
	{
		return false;
	}
	//�R�����I����č��W���X�V
	const D3DXMATRIX* matrix = m_skinModelData.GetFindBoneWorldMatrix("Character1_Reference");
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

void Player::WallShear(const D3DXVECTOR3& playerDirection)
{
	//�ǂ���̎��͈ړ����x��0�ɂ���
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_currentAnim = enAnimSetWallShear;
	m_anim.PlayAnimation(enAnimSetWallShear);
	Rotation(playerDirection);
}


void Player::WallJump(const D3DXVECTOR3& jumpDirection)
{
	//�W�����v�̃x�N�g���̑傫���𒲐�
	D3DXVECTOR3 jumpSpeed = jumpDirection;
	jumpSpeed.y = 0.0f;
	D3DXVec3Normalize(&jumpSpeed, &jumpSpeed);
	jumpSpeed *= 12.0f;
	jumpSpeed.y = m_jumpSpeed;
	m_characterController.SetMoveSpeed(jumpSpeed);
	Rotation(jumpSpeed);
	m_jumpCount = 1;
	m_currentAnim = enAnimSetWallJump;
	m_anim.PlayAnimation(enAnimSetWallJump);
	//�W�����v�����Đ�
	SoundSource* sound = New<SoundSource>(0);
	sound->Init("Assets/sound/univ0001.wav");
	sound->Play(false);
	sound->SetVolume(0.8f);
	sound = New<SoundSource>(0);
	sound->Init("Assets/sound/Jump.wav");
	sound->Play(false);
	sound->SetVolume(0.3f);
}

bool Player::SetParent(const MapChip* parent, bool parentRotation)
{
	//�e�������Ԃő��̃}�b�v�`�b�v���e�ɂȂ낤�Ƃ���Ǝ��s
	if (m_parent != nullptr && parent != nullptr)
	{
		return false;
	}
	m_parent = parent;
	//�e�q�֌W���؂ꂽ
	if (m_parent == nullptr)
	{
		return false;
	}
	else//�e�q�֌W������
	{
		//�e�̃��[�J���ł̍��W�Ɖ�]�����߂�
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
	return true;
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
	const Camera& camera = GetGameScene().GetCamera();
	//�J�����̌������ړ������Ƃ��Ĉړ�
	D3DXVECTOR3 front = camera.GetTarget() - camera.GetPosition();
	front.y = 0.0f;
	D3DXVec3Normalize(&front, &front);
	D3DXVECTOR3 side;
	//���ւ̈ړ������͊O�ς�����ċ��߂�
	D3DXVec3Cross(&side, &front, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&side, &side);

	D3DXVECTOR3 stickDir = -side * GetPad().GetLeftStickX();
	stickDir += front * GetPad().GetLeftStickY();

	const float acceleration = 0.3f;
	const float speedLimit = 16.0f;
	//�����Ă��Ȃ���
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
		//�ړ����x�����E�Ȃ�����������Ȃ�
		if (speedLimit < speed)
		{
			speed = speedLimit;
		}
		//�ǂɒ���t���ĂȂ���
		if (!m_wallJump.IsWallShear())
		{
			//�n�ʂɂ��Ă鎞
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
			else//�W�����v��
			{
				D3DXVECTOR3 jumpSpeed = stickDir;
				speed *= 0.04f;
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
		else//�ǂɒ���t���Ă�Ƃ�
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
	if (GetPad().IsTriggerButton(enButtonA) && m_jumpCount < 2 && !m_wallJump.IsWallShear())
	{
		m_currentAnim = enAnimSetJump;
		//2�f�ʂ̃W�����v�̎�
		if (m_jumpCount != 0)
		{
			if (stickDir.x != 0.0f || stickDir.z != 0.0f)
			{
				D3DXVECTOR3 jumpDir = stickDir;
				D3DXVec3Normalize(&jumpDir, &jumpDir);
				jumpDir *= D3DXVec3Length(&moveSpeed);
				moveSpeed = jumpDir;

			}
		}
		else
		{
			//�n�ʂɂ��鎞�����n�ʂ��R�鉹���Đ������
			SoundSource* jumpSound;
			jumpSound = New<SoundSource>(0);
			jumpSound->Init("Assets/sound/Jump.wav");
			jumpSound->Play(false);
			jumpSound->SetVolume(0.3f);
			//������т̎��������̃A�j���[�V�������Đ���
			if (stickDir.x == 0.0f && stickDir.z == 0.0f)
			{
				m_currentAnim = enAnimSetVerticalJump;
			}
		}
		//������Ɉړ����x��^�����
		moveSpeed.y = m_jumpSpeed;
		m_anim.PlayAnimation(m_currentAnim);
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
	}

	moveSpeed += m_stageGimmickMoveSpeed;
	m_characterController.SetMoveSpeed(moveSpeed);
	if (m_parent != nullptr)
	{
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &m_localPosition, &m_parent->GetWorldMatrix());
		m_characterController.SetPosition(position);
		m_characterController.Execute();
		position = m_characterController.GetPosition();
		D3DXMATRIX inverseMatrix;
		D3DXMatrixInverse(&inverseMatrix, NULL, &m_parent->GetWorldMatrix());
		D3DXVec3TransformCoord(&m_localPosition, &position, &inverseMatrix);
	}
	else
	{
		m_characterController.Execute();
	}

	m_movement = m_characterController.GetPosition() - m_position;
	m_position = m_characterController.GetPosition();
	m_stageGimmickMoveSpeed = { 0.0f, 0.0f, 0.0f };
}

void Player::SetStageGimmickMoveSpeed(const D3DXVECTOR3& moveSpeed)
{
	m_stageGimmickMoveSpeed += moveSpeed / GetGameTime().GetDeltaFrameTime();
}

void Player::DelayRotation(const D3DXVECTOR3& rotationDirection)
{
	D3DXVECTOR3 moveDir = rotationDirection;
	moveDir.y = 0.0f;

	D3DXQUATERNION multi;
	D3DXQuaternionIdentity(&multi);
	//���f������]
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
		//�v���C���[�̌����Ă�����ƈړ������œ��ς����ǂ̂��炢��]�����邩���߂�
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
		//�v���C���[�̌����Ă�����ƈړ������ŊO�ς�����ĉ�]�̌��������߂�
		D3DXVec3Cross(&cross, &front, &moveDir);
		if (cross.y < 0.0f)
		{
			rad = -rad;
		}
		//��]�ʂ𕪊�����B
		m_frameAngle = rad / m_rotationFrameNum;
	}
	//�܂���]���I����ĂȂ���Ή�]����
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

void Player::Rotation(const D3DXVECTOR3& rotationDirection)
{
	D3DXVECTOR3 moveDir = rotationDirection;
	moveDir.y = 0.0f;
	//�قړ����ĂȂ��Ȃ瑁�����^�[��
	if (D3DXVec3Length(&moveDir) < 0.001f)
	{
		return;
	}
	D3DXQUATERNION multi;
	D3DXQuaternionIdentity(&multi);
	//���[���h�s�񂩂�����Ă���������߂�
	D3DXMATRIX worldMat = m_skinModel.GetWorldMatrix();
	D3DXVECTOR3 front;
	front.x = worldMat.m[2][0];
	front.y = 0.0f;
	front.z = worldMat.m[2][2];
	D3DXVec3Normalize(&moveDir, &moveDir);
	D3DXVec3Normalize(&front, &front);
	//�����Ă�����ƈړ������œ��ς����
	float rad = D3DXVec3Dot(&front, &moveDir);
	//��Βl��1.0f�𒴂��Ă��ꍇ�̕␳�v�Z
	if (1.0f < rad)
	{
		rad = 1.0f;
	}
	if (rad < -1.0f)
	{
		rad = -1.0f;
	}
	rad = acosf(rad);
	//�O�ς�����Ăǂ��������ɉ񂷂�����
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &front, &moveDir);
	if (cross.y < 0.0f)
	{
		rad = -rad;
	}
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
	//�e������Ƃ��̓��[�J���ł̉�]���X�V����
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

	//�V���G�b�g�`��
	EnSkinModelShaderTechnique techniqueBackup = m_skinModel.GetCurrentShaderTechnique();
	device->GetRenderState(D3DRS_ZFUNC, &zStateBackup);
	device->GetRenderState(D3DRS_ZENABLE, &zEnableStateBackup);
	device->GetRenderState(D3DRS_ZWRITEENABLE, &zwriteEnableStateBackup);

	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	m_skinModel.SetShaderTechnique(enShaderTechniqueSilhouette);

	m_skinModel.Draw(&GetGameScene().GetCamera().GetViewMatrix(), &GetGameScene().GetCamera().GetProjectionMatrix());

	//���ʂ̕`��
	m_skinModel.SetShaderTechnique(techniqueBackup);
	device->SetRenderState(D3DRS_ZFUNC, zStateBackup);
	device->SetRenderState(D3DRS_ZENABLE, zEnableStateBackup);
	device->SetRenderState(D3DRS_ZWRITEENABLE, zwriteEnableStateBackup);
	m_skinModel.Draw(&GetGameScene().GetCamera().GetViewMatrix(), &GetGameScene().GetCamera().GetProjectionMatrix());
	m_characterController.Draw();
	m_wallJump.Draw();
}
