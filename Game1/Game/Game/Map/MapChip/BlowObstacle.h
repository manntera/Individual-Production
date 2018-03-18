#pragma once
#include "MapChip.h"
//当たると吹っ飛ばされるアイテム
class BlowObstacle : public MapChip
{
public:
	//更新関数
	void Update()override;
};