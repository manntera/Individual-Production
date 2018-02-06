#pragma once
//�Q�[���N���A�V�[���N���X

class GameClearScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameClearScene();

	//�f�X�g���N�^
	~GameClearScene();

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:
	Sprite m_sprite;		//�Q�[���N���A�̃X�v���C�g
	int		m_choiceNum;	//���ݑI��ł���I����
	Sprite m_arrow;			//���̃X�v���C�g
	Sprite m_finish;		//�^�C�g���ւ̃X�v���C�g
	Sprite m_nextStage;		//���̃X�e�[�W�ւ̃X�v���C�g
};