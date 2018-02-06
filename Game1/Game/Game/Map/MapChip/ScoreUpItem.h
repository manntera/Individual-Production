#pragma once
#include "MapChip.h"
//プレイヤーにとられるとスコアが増えるアイテム

class ScoreUpItem : public MapChip
{
public:
	//更新関数
	void Update()override;

private:

};