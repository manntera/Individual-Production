#pragma once
#include "MapChip.h"
//プレイヤーの動きを遅くするアイテム

class PlayerDelayItem : public MapChip
{
public:
	//更新関数
	void Update()override;
};