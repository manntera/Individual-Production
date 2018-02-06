#pragma once
//タイトルシーン

class TitleScene : public GameObject
{
public:
	enum EnScene
	{
		enSceneStart,
		enSceneContinue,
		enSceneTimeAttack,
	};
	//コンストラクタ
	TitleScene();

	//デストラクタ
	~TitleScene();

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void AfterDraw()override;

private:
	Sprite	m_titleBack;	//背景スプライト
	Sprite	m_title;		//タイトルロゴのスプライト
	Sprite	m_start;		//はじめからのスプライト
	Sprite	m_continue;		//つづきからのスプライト
	Sprite	m_timeAttack;	//ステージ選択へのスプライト
	Sprite	m_arrow;		//矢印のスプライト
	int		m_choiceNum;	//現在選んでいる選択肢
};