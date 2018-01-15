#pragma once
//タイム表示のＨＵＤ

class TimeSprite : public GameObject
{
public:

	//コンストラクタ
	TimeSprite();

	//デストラクタ
	~TimeSprite()override;

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

	//タイム取得
	float GetTime()
	{
		return m_time;
	}

private:
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	Sprite				m_timeSprite;
	Sprite				m_colonSprite[TIME_MAX];
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
	float				m_time;
};