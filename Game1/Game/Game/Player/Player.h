#pragma once
//�v���C���[�N���X
#include "PlayerGraspCliff.h"
#include "PlayerWallJump.h"

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
	void Start() override;

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

	D3DXMATRIX* FindBoneWorldMatrix(char* boneName)
	{
		return m_skinModelData.GetFindBoneWorldMatrix(boneName);
	}

	D3DXMATRIX GetWorldMatrix()
	{
		return m_skinModel.GetWorldMatrix();
	}


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

	void WallShear(D3DXVECTOR3 moveSpeed);

	void WallJump(D3DXVECTOR3 jumpDirection);

	void SetParent(MapChip* parent, bool parentRotation);

	void ParentChildMove();

private:
	//�ړ�����������֐�
	void Move();

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
	bool				m_isParentRotation;
	float				m_moveSpeed;
	float				m_acceleration;
	float				m_gravity;
};