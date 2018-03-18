#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;
class TimeSprite;
class GhostPlayer;
//�V�ׂ�X�e�[�W�̍ő吔
const int STAGE_NUM = 5;

//�Q�[���V�[���N���X
class GameScene : public GameObject
{
private:
	//�R���X�g���N�^
	GameScene();

	//�f�X�g���N�^
	~GameScene();

public:

	//�C���X�^���X���擾
	static GameScene& GetInstance()
	{
		static GameScene gameScene;
		return gameScene;
	}

	/*
	�������֐�
	*/
	void Init(int stageNum, bool isTimeAttack);

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//���ʑO�Ɉ�x�����Ă΂��֐�
	void BeforeDead()override;

	//�`��֐�
	void AfterDraw()override;
	
	//�J�����̎擾
	const Camera& GetCamera() const;

	//�v���C���[�̎擾
	const Player* GetPlayer() const;

	//�Q�[���N���A����Ƃ��ɊO������Ăяo���֐�
	void GameClear();

	//�Q�[���I�[�o�[�̎��ɊO������Ăяo���֐�
	void GameOver();

	void GhostDataFinish();

	//���̃X�e�[�W�̔ԍ����擾
	int GetStageNum() const
	{
		return m_stageNum;
	}

	//���������Ă���X�e�[�W�̍ő吔
	int GetStageMaxNum() const
	{
		return m_stageMaxNum;
	}

	//�Q�[���V�[�����쐬
	void Create()
	{
		Add(this, LAST_PRIORITY);
		m_isActive = true;
	}

	//�A�N�e�B�u���H
	bool IsActive() const
	{
		return m_isActive;
	}

	//���̃��[�h���I������炱�̊֐����Ă�
	void LoadComp()
	{
		m_isLoad = true;
	}

	//�Đ����ꎞ��~
	void SoundStop()
	{
		m_pBgm->Stop();
	}

	//�T�E���h���Đ�
	void SoundPlay()
	{
		m_pBgm->Play(true);
	}

private:	
	bool						m_isGameOver;			//�Q�[���I�[�o�[���H
	bool						m_isGameClear;			//�Q�[���N���A���H
	Map*						m_pMap;					//�}�b�v
	GameCamera*					m_pCamera;				//�J����
	Sky*						m_pSky;					//�X�J�C�{�b�N�X
	SoundSource*				m_pBgm;					//BGM
	int							m_stageNum;				//���݂̃X�e�[�W�̔ԍ�
	int							m_stageMaxNum;			//��Ԑi��ł���X�e�[�W�̔ԍ�
	TimeSprite*					m_pTimeSprite;			//�^�C���\���̃X�v���C�g
	bool						m_isInit;				//�������������H
	bool						m_isTimeAttack;			//�^�C���A�^�b�N���H
	GhostPlayer*				m_pGhost;				//�S�[�X�g�v���C���[
	bool						m_isActive;				//�����Ă邩����ł邩
	bool						m_isLoad;				//���[�h���I�������
	bool						m_isTimeAttackStart;	//�^�C���A�^�b�N���[�h�̎��ɃQ�[�����X�^�[�g���Ă邩�H
	std::unique_ptr<Sprite>		m_pSprite;				//�^�C���A�^�b�N���n�܂�O�̏������\���̃X�v���C�g
};

//�Q�[���V�[�����擾�B
static GameScene& GetGameScene()
{
	return GameScene::GetInstance();
}