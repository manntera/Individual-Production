#pragma once
//ゲームオーバーシーンクラス

class GameOverScene : public GameObject
{
public:
	//コンストラクタ
	GameOverScene();

	//デストラクタ
	~GameOverScene();

	/*
	初期化関数
	isTimeAttack	タイムアタックかどうか
	*/
	void Init(bool isTimeAttack)
	{
		m_isTimeAttack = isTimeAttack;
	}

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;
	
	//描画関数
	void Draw()override;
private:
	Sprite	m_sprite;		//ゲームオーバーのスプライト
	int		m_choiceNum;	//現在選んでいる選択肢
	Sprite	m_arrow;		//矢印のスプライト
	Sprite	m_retry;		//リトライのスプライト
	Sprite	m_finish;		//タイトルへのスプライト
	bool	m_isTimeAttack;	//タイムアタックモードかどうか
};