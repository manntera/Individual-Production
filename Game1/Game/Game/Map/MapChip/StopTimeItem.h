#pragma once
#include "MapChip.h"
//ステージギミックの動きを止めることができるアイテム

class StopTimeItem : public MapChip
{
public:
	//更新関数
	void Update()override;

private:
};