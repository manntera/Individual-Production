#pragma once
//�Q�[���I�[�o�[�V�[���N���X

class GameOverScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameOverScene();

	//�f�X�g���N�^
	~GameOverScene();

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;
	
	//�`��֐�
	void Draw()override;
private:

	Sprite m_sprite;		//�Q�[���I�[�o�[�̃X�v���C�g
};