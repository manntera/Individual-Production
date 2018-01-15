#pragma once
//�Q�[���I�[�o�[�V�[���N���X

class GameOverScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameOverScene();

	//�f�X�g���N�^
	~GameOverScene();

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
	Sprite m_sprite;		//�Q�[���I�[�o�[�̃X�v���C�g
	int	   m_choiceNum;
	Sprite m_arrow;
	Sprite m_retry;
	Sprite m_finish;
	bool	m_isTimeAttack;
};