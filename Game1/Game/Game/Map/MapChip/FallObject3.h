#pragma once
#include "MapChip.h"
//落ちるオブジェクト

class FallObject3 : public MapChip
{
public:
	//コンストラクタ
	FallObject3();

	//デストラクタ
	~FallObject3();

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
	//パーティクルを消去
	void ParticleDelete();

	//サウンドを消去
	void SoundDelete();

	//再初期化
	void Reset();

	//パーティクルを出す
	void ParticleEmitt();
private:
	bool				m_isFall;			//落ち始めたか
	RigidBody			m_rigidBody;		//剛体
	BoxCollider			m_boxCollider;		//コライダー
	ParticleEmitter*	m_particle;			//パーティクル
	float				m_timer;			//消えるまでの時間
	float				m_animationTimer;	//揺れるアニメーションをする時間	
	D3DXVECTOR3			m_animationMove;	//揺れるアニメーションをするための移動速度
	SoundSource*		m_pSound;			//サウンド
	float				m_soundVolume;		//サウンドのボリューム
	float				m_revivalTime;		//死んでから復活するまでの時間
	bool				m_isDead;			//死んでるか？
	D3DXVECTOR3			m_initPos;			//初期化用の座標
};