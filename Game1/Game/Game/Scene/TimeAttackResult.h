#pragma once
#include "GameScene.h"

class TimeAttackResult : public GameObject
{
public:
	TimeAttackResult();

	~TimeAttackResult();

	void Init(float time);

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;
private:
	int		m_choiceNum;
	Sprite m_arrow;
	Sprite m_finish;
	Sprite m_retry;
	int		m_rankNum;
	Sprite m_back;		//ゲームクリアのスプライト
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