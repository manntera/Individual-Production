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

	//
	bool IsWallJump()
	{
		return m_isWallJump;
	}

private:
	BoxCollider				m_boxCollider;			//�ǂƂ̂����蔻������R���C�_�[
	CollisionDetection		m_wallDetection;		//�ǂƂ̂����蔻��
	Player*					m_player;				//�v���C���[
	bool					m_isWallShear;			//�ǂ��蒆���H
	bool					m_isWallJump;			//�ǃW�����v�����H
	CharacterController*	m_characterController;	//�v���C���[�̃L�����N�^�[�R���g���[���[
	D3DXVECTOR3				m_wallJumpDirection;	//�ǃW�����v����Ƃ��̕���
	float					m_wallShearGravity;		//�ǂ���̎��̏d��
	float					m_defaultGravity;		//���ʂ̎��̏d��
	ParticleEmitter*		m_wallDust;
	D3DXMATRIX*				m_dustPos;
};