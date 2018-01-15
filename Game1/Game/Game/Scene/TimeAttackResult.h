#pragma once


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
	float m_time;
	Sprite m_back;		//ゲームクリアのスプライト
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	Sprite				m_timeSprite;
	Sprite				m_colonSprite[TIME_MAX];
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
};