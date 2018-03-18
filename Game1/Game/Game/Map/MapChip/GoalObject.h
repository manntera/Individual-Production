#pragma once
#include "MapChip.h"
//ゴールを示すオブジェクト

class GoalObject : public MapChip
{
public:
	//コンストラクタ
	GoalObject();

	//デストラクタ
	~GoalObject();

	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	void Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim = nullptr)override;

	//更新関数
	void Update()override;
private:
	D3DXQUATERNION m_multi;	//毎フレーム回転させるのに使うクォーターニオン
};