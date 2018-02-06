#pragma once
//ゲームクリアシーンクラス

class GameClearScene : public GameObject
{
public:
	//コンストラクタ
	GameClearScene();

	//デストラクタ
	~GameClearScene();

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;
private:
	Sprite m_sprite;		//ゲームクリアのスプライト
	int		m_choiceNum;	//現在選んでいる選択肢
	Sprite m_arrow;			//矢印のスプライト
	Sprite m_finish;		//タイトルへのスプライト
	Sprite m_nextStage;		//次のステージへのスプライト
};