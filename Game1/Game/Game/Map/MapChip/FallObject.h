#pragma once
#include "MapChip.h"
//落ちるオブジェクト

class FallObject : public MapChip
{
public:
	//コンストラクタ
	FallObject();

	//デストラクタ
	~FallObject();

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
	void Draw()override;

	//パーティクルを消去
	void ParticleDelete();

private:
	bool				m_isActive;			//アクティブかどうか
	RigidBody			m_rigidBody;		//剛体
	BoxCollider			m_boxCollider;		//コライダー
	ParticleEmitter*	m_particle;			//パーティクル
	float				m_timer;			//消えるまでの時間
};