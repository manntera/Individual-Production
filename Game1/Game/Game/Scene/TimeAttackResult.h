#pragma once
#include "GameScene.h"

class TimeAttackResult : public GameObject
{
public:
	TimeAttackResult();

	~TimeAttackResult();

	void Init(float time);

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:
	int		m_choiceNum;
	Sprite m_arrow;
	Sprite m_finish;
	Sprite m_retry;
	int		m_rankNum;
	Sprite m_back;		//�Q�[���N���A�̃X�v���C�g
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	static const int	RANK_NUM = 5;
	Sprite				m_colonSprite[RANK_NUM][TIME_MAX];
	Sprite				m_numSprite[RANK_NUM][TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
	static int			m_times[STAGE_NUM][RANK_NUM + 1];
	float				m_alpha;
	int					m_stageNum;
};