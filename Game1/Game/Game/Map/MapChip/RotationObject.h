#pragma once
#include "MapChip.h"
//回転オブジェクト

class RotationObject : public MapChip
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

	//描画関数
	void Draw();
private:
	RigidBody		m_rigidBody;		//剛体
	MeshCollider	m_meshCollider;		//コライダー
	bool			m_isChild;			//子供がいるかどうか
	D3DXQUATERNION	m_multi;			//回転量
};