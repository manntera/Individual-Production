#pragma once
//�v���C���[�̕ǂ����ǃW�����v������N���X
class Player;


class PlayerWallJump
{
public:

	//�R���X�g���N�^
	PlayerWallJump();

	//�f�X�g���N�^
	~PlayerWallJump();

	/*
	������
	player					�v���C���[
	characterController		�v���C���[�̃L�����R��
	*/
	void Init(Player* player, CharacterController* characterController);

	//�X�V
	void Update();

	//�ǂ��蒆���H
	bool IsWallShear()
	{
		return m_isWallShear;
	}

	//�ǃW�����v������
	bool IsWallJump()
	{
		return m_isWallJump && m_wallJumpCount ==0;
	}

	//�`��֐�
	void Draw();

private:

	BoxCollider				m_groundCollider;		//�n�ʂƂ̂����蔻������R���C�_�[
	BoxCollider				m_wallCollider;			//�ǂƂ̂����蔻������R���C�_�[
	CollisionDetection		m_wallDetection;		//�ǂƂ̂����蔻��
	CollisionDetection		m_groundDetection;		//�n�ʂƂ̂����蔻��(�L�����N�^�[�R���g���[���[��IsOnGround���g���ƃ��b�V���Ȃǂō��̂�����Ă����ꍇ�Ƀ|���S���̐؂�ڂɔ��肪�����Ă��܂�
	Player*					m_player;				//�v���C���[
	bool					m_isWallShear;			//�ǂ��蒆���H
	bool					m_isWallJump;			//�ǃW�����v�����H
	CharacterController*	m_characterController;	//�v���C���[�̃L�����N�^�[�R���g���[���[
	D3DXVECTOR3				m_wallJumpDirection;	//�ǃW�����v����Ƃ��̕���
	float					m_wallShearGravity;		//�ǂ���̎��̏d��
	float					m_defaultGravity;		//���ʂ̎��̏d��
	ParticleEmitter*		m_wallDust;				//�p�[�e�B�N��
	D3DXMATRIX*				m_dustPos;				//�p�[�e�B�N�����o�����̈ʒu
	int						m_wallJumpCount;		//�ǃW�����v���Ă���̃J�E���^�[
};