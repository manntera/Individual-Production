#pragma once
//�^�C�g���V�[��

class TitleScene : public GameObject
{
public:
	enum EnScene
	{
		enSceneStart,
		enSceneContinue,
		enSceneTimeAttack,
	};
	//�R���X�g���N�^
	TitleScene();

	//�f�X�g���N�^
	~TitleScene();

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void AfterDraw()override;

private:
	Sprite	m_titleBack;	//�w�i�X�v���C�g
	Sprite	m_title;		//�^�C�g�����S�̃X�v���C�g
	Sprite	m_start;		//�͂��߂���̃X�v���C�g
	Sprite	m_continue;		//�Â�����̃X�v���C�g
	Sprite	m_timeAttack;	//�X�e�[�W�I���ւ̃X�v���C�g
	Sprite	m_arrow;		//���̃X�v���C�g
	int		m_choiceNum;	//���ݑI��ł���I����
};