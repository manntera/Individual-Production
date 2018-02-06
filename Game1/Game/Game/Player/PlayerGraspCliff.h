#pragma once
class Player;
//�v���C���[���R�����ޏ���������N���X

class PlayerGraspCliff
{
public:

	//�R���X�g���N�^
	PlayerGraspCliff();

	//�f�X�g���N�^
	~PlayerGraspCliff();

	/*
	�������֐�
	player		�g���v���C���[
	height		�v���C���[�̍���
	*/
	void Init(Player* player, float height);

	//�X�V�֐�
	void Update();

	//�R������Ă��邩�H
	bool IsActive() const
	{
		return m_isActive;
	}

	//�`��֐�
	void Draw();

private:	
	CollisionDetection	m_cliffRiseDetectionLow;	//�R�����񂾂��̂����蔻��
	CollisionDetection	m_cliffRiseDetectionUp;		//�R�����񂾂��̂����蔻��
	CollisionDetection  m_cliffRiseDetectionBack;	//�R�����񂾊��������̂����蔻��
	BoxCollider			m_boxCollider;				//�����蔻��Ɏg���R���C�_�[
	Player*				m_player;					//�v���C���[
	float				m_playerHeight;				//�v���C���[�̍���
	bool				m_isActive;					//�R������Ă��邩�Htrue�Ȃ����Ă���r���Afalse�Ȃ����Ă��Ȃ�
};