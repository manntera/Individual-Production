#pragma once
#include "MapChip.h"

//背景オブジェクト

class StaticMapObject : public MapChip
{
public:
	//コンストラクタ
	StaticMapObject();

	//デストラクタ
	~StaticMapObject();

	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	void Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim = nullptr)override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

private:
	RigidBody		m_rigidBody;		//剛体
	BoxCollider		m_boxCollider;		//コライダー
};
