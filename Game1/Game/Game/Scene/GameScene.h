#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;
class TimeSprite;
class GhostPlayer;

//�Q�[���V�[���N���X

class GameScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameScene();

	//�f�X�g���N�^
	~GameScene();

	void Init(int stageNum, bool isTimeAttack);

	//�������֐�
	bool Start()override;

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

	void GhostDataFinish();

	//���̃X�e�[�W�̔ԍ����擾
	static int GetStageNum()
	{
		return m_stageNum;
	}

	static int GetStageMaxNum()
	{
		return m_stageMaxNum;
	}

private:

	bool			m_isGameOver;	//�Q�[���I�[�o�[���H
	bool			m_isGameClear;	//�Q�[���N���A���H
	Map*			m_map;			//�}�b�v
	GameCamera*		m_camera;		//�J����
	Sky*			m_sky;			//�X�J�C�{�b�N�X
	SoundSource*	m_bgm;			//BGM
	static int		m_stageNum;		//���݂̃X�e�[�W�̔ԍ�
	static int		m_stageMaxNum;	//��Ԑi��ł���X�e�[�W�̔ԍ�
	TimeSprite*		m_pTimeSprite;	//�^�C���\���̃X�v���C�g
	bool			m_isInit;		//�������������H
	bool			m_isTimeAttack;	//�^�C���A�^�b�N���H
	GhostPlayer*	m_pGhost;		//�S�[�X�g�v���C���[
};
const int STAGE_NUM = 3;
extern GameScene *g_gameScene;