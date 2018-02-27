#pragma once
//�v���C���[�N���X
#include "PlayerGraspCliff.h"
#include "PlayerWallJump.h"
class GhostPlayer;

enum EnAnimationSet
{
	enAnimSetRun,
	enAnimSetWait,
	enAnimSetWallShear,
	enAnimSetWallJump,
	enAnimSetJump,
	enAnimSetCliffRise,
	enAnimSetVerticalJump,
	enAnimSetDelight,
	enAnimSetNum,
};
class MapChip;


class Player : public GameObject
{
public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	/*
	�������֐�
	position	�v���C���[�̍��W
	rotation	�v���C���[�̉�]
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);

	//�������֐�
	bool Start() override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	//�`��֐�
	void AfterDraw() override;

	//���W���擾
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}

	/*
	�X�e�[�W�M�~�b�N�ɂ��v���C���[����������鎞�̈ړ����x��ݒ�B
	moveSpeed	�v���C���[�𓮂��������Ƒ��x
	*/
	void SetStageGimmickMoveSpeed(const D3DXVECTOR3& moveSpeed);

	/*
	�{�[���̖��O�����Ń{�[���̃��[�h�s����擾�B
	boneName	�{�[���̖��O
	ret			�{�[���̃��[���h�s��̃|�C���^
	*/
	const D3DXMATRIX* FindBoneWorldMatrix(const char* boneName) const
	{
		return m_skinModelData.GetFindBoneWorldMatrix(boneName);
	}

	//���[���h�s����擾�B
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

	//1�t���[���ł̈ړ��ʂ��擾�B
	const D3DXVECTOR3& GetMovement() const
	{
		return m_movement;
	}

	/*
	�R�����Ƃ���PlayerGraspCliff����Ăяo���֐�
	moveDirection	�ǂ̖@��
	*/
	void CliffRiseStart(const D3DXVECTOR3& moveDirection);

	/*
	�R������Ă��鎞��PlayerGraspCliff����Ăяo���֐�
	ret		�R�����I��������Htrue�Ȃ���I������Afalse�Ȃ�܂�����Ă���r��
	*/
	bool CriffRiseEnd();

	/*
	�ǂɒ���t�������ɌĂяo���֐�
	playerDirection		�v���C���[�̕���
	*/
	void WallShear(const D3DXVECTOR3& playerDirection);

	/*
	�ǃW�����v���鎞�ɌĂяo���֐�
	jumpDirection		�v���C���[���W�����v�������
	*/
	void WallJump(const D3DXVECTOR3& jumpDirection);

	/*
	�e�q�֌W��������O�����肷��֐�
	parent�@		�e�̃|�C���^�B�e�q�֌W���O���ꍇ��nullptr��n���΂����B
	parentRotation	��]���e�q�֌W�����邩�ۂ�
	return			�e�q�֌W���������Htrue�Ȃ�����Afalse�Ȃ�e�q�֌W����̂Ɏ��s�������e�q�֌W���؂ꂽ
	*/
	bool SetParent(const MapChip* parent, bool parentRotation);

	//���f���f�[�^���擾
	const SkinModelData& GetSkinModelData() const
	{
		return m_skinModelData;
	}

	/*
	�S�[�X�g�f�[�^�̌v���J�n
	time	�X�e�[�W�̃N���A�^�C��
	isClear	�X�e�[�W���N���A�������H
	*/
	void GhostDataFinish(float time, bool isClear) const;

	//�S�[�X�g�f�[�^�̌v���J�n
	void GhostDataStart() const;

	//���C�g���擾
	const Light& GetLight() const
	{
		return m_light;
	}

	void MoveSpeedDelay()
	{
		m_delayTime = 6.0f;
	}

	void Invincible();
	
	void BlowObstacle();
private:
	//�ړ�����������֐�
	void Move(float deltaTime);

	//���f�����ړ������ɍ��킹�ăf�B���C�������Ȃ����]������֐�
	void DelayRotation(const D3DXVECTOR3& rotationDirection);

	//���f�����ړ������ɍ��킹�ĉ�]������֐�
	void Rotation(const D3DXVECTOR3& rotationDirection);

	void PlayAnimation(EnAnimationSet animationSet);

private:
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	Light				m_light;				//���f���̃��C�g
	D3DXQUATERNION		m_rotation;				//���f���̉�]
	D3DXQUATERNION		m_localRotation;		//�e������Ƃ��̐e���猩�����[�J�����W
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_localPosition;		//�e������Ƃ��̐e���猩�����[�J���ȉ�]
	D3DXVECTOR3			m_scale;				//���f���̃T�C�Y
	Animation			m_anim;					//�A�j���[�V����
	CharacterController m_characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_stageGimmickMoveSpeed;//�X�e�[�W�M�~�b�N�ɂ���ăv���C���[�𓮂�����鎞�̈ړ����x
	D3DXVECTOR3			m_movement;				//1�t���[���ňړ���������
	PlayerWallJump		m_wallJump;				//�ǃW�����v���Ă����z
	int					m_jumpCount;			//�W�����v������
	EnAnimationSet		m_currentAnim;			//���ݍĐ����Ă�A�j���[�V����
	bool				m_isJump;				//�W�����v���Ă邩�H
	const MapChip*		m_parent;				//�e
	bool				m_isParentRotation;		//��]�̐e�q�֌W�����Ă��邩
	float				m_moveSpeed;			//�ړ����x
	float				m_acceleration;			//�����x
	const int			m_rotationFrameNum;		//��]����`��Ԃ��鎞�Ɏg���t���[����
	float				m_frameAngle;			//1�t���[���ŉ�]�����]��
	int					m_rotationCount;		//��]����`��Ԃ��邽�߂̃J�E���^�[
	const float			m_jumpSpeed;
	float				m_delayTime;
	bool				m_isInvincible;			
	float				m_invincibleTime;
	bool				m_isObstacle;
	float				m_obstacleTime;
};






