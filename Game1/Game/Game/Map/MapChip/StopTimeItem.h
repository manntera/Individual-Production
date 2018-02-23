#pragma once
#include "MapChip.h"
//ステージギミックの動きを止めることができるアイテム

class StopTimeItem : public MapChip
{
public:
	//コンストラクタ
	StopTimeItem();


	//更新関数
	void Update()override;

	void Draw()override;

private:
	bool	m_isDead;
	float	m_revivalTime;
};