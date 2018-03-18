#pragma once
#include "GameScene.h"
//�^�C���A�^�b�N�̎��̃��U���g�V�[��
static const int	RANK_NUM = 5;								//���ʂ܂ł��邩�̐�

class TimeAttackResult : public GameObject
{
public:
	//�R���X�g���N�^
	TimeAttackResult();

	//�f�X�g���N�^
	~TimeAttackResult();

	/*
	�������֐�
	time	����̃N���A�^�C��
	*/
	void Init(float time);

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;

	//�^�C���̋L�^��ǂݍ���
	static void TimeDataRead();

	//�^�C���̋L�^���Z�[�u
	static void TimeDataSave();

	//�^�C�����擾
	const static float GetTime(int stageNum, int rankNum)
	{
		return (float)m_times[stageNum][rankNum] / 100.0f;
	}

private:
	static const int	NUM_MAX = 10;								//�ꌅ�̐����̐�
	static const int	DIGIT_MAX = 2;								//���̐�
	static const int	TIME_MAX = 3;								//��؂�̐�
	int					m_choiceNum;								//���ݑI��ł���I����
	Sprite				m_arrow;									//���̃X�v���C�g
	Sprite				m_finish;									//�^�C�g���ւ̃X�v���C�g
	Sprite				m_retry;									//���g���C�̃X�v���C�g
	int					m_rankNum;									//����̃^�C���̏���
	Sprite				m_back;										//�Q�[���N���A�̃X�v���C�g
	Sprite				m_colonSprite[RANK_NUM][TIME_MAX];			//��؂�̃X�v���C�g
	Sprite				m_numSprite[RANK_NUM][TIME_MAX][DIGIT_MAX];	//�����̃X�v���C�g
	Texture*			m_numTexture[NUM_MAX];						//�����̃e�N�X�`��
	static int			m_times[STAGE_NUM][RANK_NUM + 1];			//�^�C���̋L�^
	float				m_alpha;									//����̃^�C���̃X�v���C�g��_�ł����邽�߂̃A���t�@�l
	int					m_stageNum;									//�N���A�����X�e�[�W�̔ԍ�
};