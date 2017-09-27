#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;

//�Q�[���V�[���N���X

class GameScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameScene();

	//�f�X�g���N�^
	~GameScene();

	//�������֐�
	void Start()override;

	//�X�V�֐�
	void Update()override;

	//���ʑO�Ɉ�x�����Ă΂��֐�
	void BeforeDead()override;
	
	//�J�����̎擾
	Camera& GetCamera();

	//�v���C���[�̎擾
	Player* GetPlayer();

	//�Q�[���N���A����Ƃ��ɊO������Ăяo���֐�
	void GameClear();

	//�Q�[���I�[�o�[�̎��ɊO������Ăяo���֐�
	void GameOver();

private:
	Map*			m_map;		//�}�b�v
	GameCamera*		m_camera;	//�J����
	Sky*			m_sky;		//�X�J�C�{�b�N�X
};

extern GameScene *g_gameScene;