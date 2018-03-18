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

	//描画関数
	void Draw()override;

private:
	bool	m_isDead;					//死んでるか？
	float	m_revivalTime;				//復活するまでの時間
};