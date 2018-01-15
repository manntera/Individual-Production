#pragma once
//ゲームオーバーシーンクラス

class GameOverScene : public GameObject
{
public:
	//コンストラクタ
	GameOverScene();

	//デストラクタ
	~GameOverScene();

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
	Sprite m_sprite;		//ゲームオーバーのスプライト
	int	   m_choiceNum;
	Sprite m_arrow;
	Sprite m_retry;
	Sprite m_finish;
	bool	m_isTimeAttack;
};