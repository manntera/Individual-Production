#pragma once
//ゲームクリアシーンクラス

class GameClearScene : public GameObject
{
public:
	//コンストラクタ
	GameClearScene();

	//デストラクタ
	~GameClearScene();

	void Init(float time);

	//初期化関数
	void Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;
private:
	float m_time;
	Sprite m_sprite;		//ゲームクリアのスプライト
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	Sprite				m_timeSprite;
	Sprite				m_colonSprite[TIME_MAX];
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
};