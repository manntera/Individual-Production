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
	void Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:
	Sprite m_sprite;		//�Q�[���N���A�̃X�v���C�g
};