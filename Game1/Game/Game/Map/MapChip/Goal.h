#pragma once
#include "MapChip.h"
//ゴールクラス、プレイヤーが当たるとゲームクリアになる

class Goal : public MapChip
{
public:
	//コンストラクタ
	Goal();

	//デストラクタ
	~Goal();

	//更新関数
	void Update()override;

private:
};