#pragma once
#include "GameScene.h"
//タイムアタックの時のリザルトシーン
static const int	RANK_NUM = 5;								//何位まであるかの数

class TimeAttackResult : public GameObject
{
public:
	//コンストラクタ
	TimeAttackResult();

	//デストラクタ
	~TimeAttackResult();

	/*
	初期化関数
	time	今回のクリアタイム
	*/
	void Init(float time);

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

	//タイムの記録を読み込み
	static void TimeDataRead();

	//タイムの記録をセーブ
	static void TimeDataSave();

	//タイムを取得
	const static float GetTime(int stageNum, int rankNum)
	{
		return (float)m_times[stageNum][rankNum] / 100.0f;
	}

private:
	static const int	NUM_MAX = 10;								//一桁の数字の数
	static const int	DIGIT_MAX = 2;								//桁の数
	static const int	TIME_MAX = 3;								//区切りの数
	int					m_choiceNum;								//現在選んでいる選択肢
	Sprite				m_arrow;									//矢印のスプライト
	Sprite				m_finish;									//タイトルへのスプライト
	Sprite				m_retry;									//リトライのスプライト
	int					m_rankNum;									//今回のタイムの順位
	Sprite				m_back;										//ゲームクリアのスプライト
	Sprite				m_colonSprite[RANK_NUM][TIME_MAX];			//区切りのスプライト
	Sprite				m_numSprite[RANK_NUM][TIME_MAX][DIGIT_MAX];	//数字のスプライト
	Texture*			m_numTexture[NUM_MAX];						//数字のテクスチャ
	static int			m_times[STAGE_NUM][RANK_NUM + 1];			//タイムの記録
	float				m_alpha;									//今回のタイムのスプライトを点滅させるためのアルファ値
	int					m_stageNum;									//クリアしたステージの番号
};