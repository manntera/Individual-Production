#pragma once
#include "GhostCommon.h"
//ゴーストデータを再生するクラス

class GhostPlayer : public GameObject
{
public:
	//コンストラクタ
	GhostPlayer();

	//デストラクタ
	~GhostPlayer();

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

private:
	SkinModelData							m_modelData;			//スキンモデルデータ
	SkinModel								m_model;				//スキンモデル
	Animation								m_animation;			//アニメーション
	std::list<GhostData>::const_iterator	m_ghostData;			//ゴーストデータのイテレーター
	int										m_currentAnimationNum;	//現在再生中のアニメーションの番号
	Light									m_light;				//モデルのライト
	bool									m_isGoal;				//ゴールしたか？
};