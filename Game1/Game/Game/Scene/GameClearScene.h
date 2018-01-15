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
	int		m_choiceNum;	//現在選んでいる選択肢の番号
	Sprite m_arrow;			
	Sprite m_finish;		
	Sprite m_nextStage;
};