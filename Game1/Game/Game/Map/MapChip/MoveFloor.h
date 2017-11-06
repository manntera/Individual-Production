#pragma once
#include "MapChip.h"

class MoveFloor : public MapChip
{
public:
	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr)override;

	//更新関数
	void Update()override;
private:
	float			m_timer;
	D3DXVECTOR3		m_moveSpeed;
	RigidBody		m_rigidBody;		//剛体
	BoxCollider		m_boxCollider;		//コライダー
	bool			m_isChild;			//子供がいるかどうか
};