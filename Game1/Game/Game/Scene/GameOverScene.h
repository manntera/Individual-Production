#pragma once
//�Q�[���I�[�o�[�V�[���N���X

class GameOverScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameOverScene();

	//�f�X�g���N�^
	~GameOverScene();

	/*
	�������֐�
	isTimeAttack	�^�C���A�^�b�N���ǂ���
	*/
	void Init(bool isTimeAttack)
	{
		m_isTimeAttack = isTimeAttack;
	}

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;
	
	//�`��֐�
	void Draw()override;
private:
	Sprite	m_sprite;		//�Q�[���I�[�o�[�̃X�v���C�g
	int		m_choiceNum;	//���ݑI��ł���I����
	Sprite	m_arrow;		//���̃X�v���C�g
	Sprite	m_retry;		//���g���C�̃X�v���C�g
	Sprite	m_finish;		//�^�C�g���ւ̃X�v���C�g
	bool	m_isTimeAttack;	//�^�C���A�^�b�N���[�h���ǂ���
};