#pragma once
#include "MapChip.h"
//プレイヤーの動きを遅くするアイテム

class PlayerDelayItem : public MapChip
{
public:
	void Update()override;
};