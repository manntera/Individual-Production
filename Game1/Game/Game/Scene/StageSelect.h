#pragma once
#include "GameScene.h"
//�X�e�[�W��I������V�[��

class StageSelect : public GameObject
{
public:
	//�R���X�g���N�^
	StageSelect();

	//�f�X�g���N�^
	~StageSelect();

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;

	void SetBGM(SoundSource* sound)
	{
		m_pBgm = sound;
	}

private:
	Sprite	m_stageNum[STAGE_NUM];	//�X�e�[�W�ԍ��̃X�v���C�g
	Sprite	m_arrow;				//���̃X�v���C�g
	Sprite	m_back;					//�w�i�̃X�v���C�g
	int		m_choiceNum;			//���ݑI��ł���I����
	bool	m_isBackScene;			//�^�C�g���֖߂邩�̃t���O
	SoundSource* m_pBgm;
};