#pragma once
#include "MapChip.h"
//このアイテムを取ると一部のアイテムをとっても無効化できる

class InvincibleItem : public MapChip
{
public:
	//更新関数
	void Update()override;

};