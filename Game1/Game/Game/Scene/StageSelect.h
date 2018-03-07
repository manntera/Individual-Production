#pragma once
#include "GameScene.h"
//ステージを選択するシーン

class StageSelect : public GameObject
{
public:
	//コンストラクタ
	StageSelect();

	//デストラクタ
	~StageSelect();

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

	void SetBGM(SoundSource* sound)
	{
		m_pBgm = sound;
	}

private:
	Sprite	m_stageNum[STAGE_NUM];	//ステージ番号のスプライト
	Sprite	m_arrow;				//矢印のスプライト
	Sprite	m_back;					//背景のスプライト
	int		m_choiceNum;			//現在選んでいる選択肢
	bool	m_isBackScene;			//タイトルへ戻るかのフラグ
	SoundSource* m_pBgm;
};