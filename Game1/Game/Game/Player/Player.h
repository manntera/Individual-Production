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

	//���W���擾
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}

	/*
	�X�e�[�W�M�~�b�N�ɂ��v���C���[����������鎞�̈ړ����x��ݒ�B
	moveSpeed	�v���C���[�𓮂��������Ƒ��x
	*/
	void SetStageGimmickMoveSpeed(D3DXVECTOR3 moveSpeed);

	/*
	�{�[���̖��O�����Ń{�[���̃��[�h�s����擾�B
	boneName	�{�[���̖��O
	ret			�{�[���̃��[���h�s��̃|�C���^
	*/
	D3DXMATRIX* FindBoneWorldMatrix(char* boneName)
	{
		return m_skinModelData.GetFindBoneWorldMatrix(boneName);
	}

	//���[���h�s����擾�B
	D3DXMATRIX GetWorldMatrix()
	{
		return m_skinModel.GetWorldMatrix();
	}

	//1�t���[���ł̈ړ��ʂ��擾�B
	D3DXVECTOR3 GetMovement()
	{
		return m_movement;
	}

	/*
	�R�����Ƃ���PlayerGraspCliff����Ăяo���֐�
	moveDirection	�ǂ̖@��
	*/
	void CliffRiseStart(D3DXVECTOR3 moveDirection);

	/*
	�R������Ă��鎞��PlayerGraspCliff����Ăяo���֐�
	ret		�R�����I��������Htrue�Ȃ���I������Afalse�Ȃ�܂�����Ă���r��
	*/
	bool CriffRiseEnd();

	/*
	�ǂɒ���t�������ɌĂяo���֐�
	playerDirection		�v���C���[�̕���
	*/
	void WallShear(D3DXVECTOR3 playerDirection);

	/*
	�ǃW�����v���鎞�ɌĂяo���֐�
	jumpDirection		�v���C���[���W�����v�������
	*/
	void WallJump(D3DXVECTOR3 jumpDirection);

	/*
	�e�q�֌W��������O�����肷��֐�
	parent�@		�e�̃|�C���^�B�e�q�֌W���O���ꍇ��nullptr��n���΂����B
	parentRotation	��]���e�q�֌W�����邩�ۂ�
	*/
	bool SetParent(MapChip* parent, bool parentRotation);

	//���f���f�[�^���擾
	SkinModelData& GetSkinModelData()
	{
		return m_skinModelData;
	}

	/*
	�S�[�X�g�f�[�^�̌v���J�n
	time	�X�e�[�W�̃N���A�^�C��
	isClear	�X�e�[�W���N���A�������H
	*/
	void GhostDataFinish(float time, bool isClear);

	//�S�[�X�g�f�[�^�̌v���J�n
	void GhostDataStart();

	//���C�g���擾
	Light& GetLight()
	{
		return m_light;
	}
private:
	//�ړ�����������֐�
	void Move();

	//���f�����ړ������ɍ��킹�ăf�B���C�������Ȃ����]������֐�
	void DelayRotation(D3DXVECTOR3 rotationDirection);

	//���f�����ړ������ɍ��킹�ĉ�]������֐�
	void Rotation(D3DXVECTOR3 rotationDirection);

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
	Texture				m_modelNormalMap;		//���f���̖@���}�b�v
	Texture				m_modelSpecularMap;		//���f���̃X�y�L�����}�b�v
	D3DXVECTOR3			m_stageGimmickMoveSpeed;//�X�e�[�W�M�~�b�N�ɂ���ăv���C���[�𓮂�����鎞�̈ړ����x
	D3DXVECTOR3			m_movement;				//1�t���[���ňړ���������
	PlayerGraspCliff	m_graspCliff;			//�R�͂�ł����z
	PlayerWallJump		m_wallJump;				//�ǃW�����v���Ă����z
	int					m_jumpCount;			//�W�����v������
	EnAnimationSet		m_currentAnim;			//���ݍĐ����Ă�A�j���[�V����
	bool				m_isJump;				//�W�����v���Ă邩�H
	MapChip*			m_parent;				//�e
	bool				m_isParentRotation;		//��]�̐e�q�֌W�����Ă��邩
	float				m_moveSpeed;			//�ړ����x
	float				m_acceleration;			//�����x
	int					m_rotationFrameNum;		//��]����`��Ԃ��鎞�Ɏg���t���[����
	float				m_frameAngle;			//1�t���[���ŉ�]�����]��
	int					m_rotationCount;		//��]����`��Ԃ��邽�߂̃J�E���^�[
};