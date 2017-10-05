#pragma once
//�v���C���[�N���X

enum EnAnimationSet
{
	enAnimSetRun,
	enAnimSetWait,
	enAnimSetWallShear,
	enAnimSetWallJump,
	enAnimSetJump,
	enAnimSetNum,
};

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

private:
	//�ړ�����������֐�
	void Move();

	void Jump();

	//���f�����ړ������ɍ��킹�ĉ�]������֐�
	void Rotation();

private:
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	Light				m_light;				//���f���̃��C�g
	D3DXQUATERNION		m_rotation;				//���f���̉�]
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_scale;				//���f���̃T�C�Y
	Animation			m_anim;					//�A�j���[�V����
	CharacterController m_characterController;	//�L�����N�^�[�R���g���[���[
	Texture				m_modelNormalMap;		//���f���̖@���}�b�v
	Texture				m_modelSpecularMap;		//���f���̃X�y�L�����}�b�v
	D3DXVECTOR3			m_stageGimmickMoveSpeed;//�X�e�[�W�M�~�b�N�ɂ���ăv���C���[�𓮂�����鎞�̈ړ����x
	int					m_jumpCount;
	bool				m_isWallShear;
	float				m_wallShearGravity;
	float				m_defaultGravity;
	D3DXVECTOR3			m_wallJumpDirection;
	EnAnimationSet		m_currentAnim;
};