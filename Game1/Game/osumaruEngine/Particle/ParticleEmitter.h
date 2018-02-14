#pragma once
class Particle;
class Camera;
#include "../Graphics/Texture.h"

struct SParticleEmittInfo
{
	char*	filePath;			//テクスチャのファイルパス
	float width;				//パーティクルの横幅
	float height;				//パーティクルの縦幅
	D3DXVECTOR4 uv;				//テクスチャのuv座標。左上のuv、右下のuv
	D3DXVECTOR3 randomPosition;		//パーティクル座標のランダム幅
	D3DXVECTOR3 gravity;		//パーティクルの重力
	float	lifeTime;			//パーティクルの寿命
	float	emittIntervalTime;	//パーティクルが出るインターバルの時間
	float	emitterLifeTime;	//エミッターの寿命
	D3DXVECTOR3 emitterPosition;//エミッターの座標
	int particleNum;			//同時に出るパーティクルの数
	bool isFirstTimeRandom;		//一番最初にパーティクル出すときだけ時間をずらすか
};

//パーティクルエミッター
class ParticleEmitter : public GameObject
{
public:
	//コンストラクタ
	ParticleEmitter();

	//デストラクタ
	~ParticleEmitter();

	/*
	エミッターの初期化
	info　パーティクルとエミッターの初期化情報
	camera	ビルボード処理に使うカメラ
	*/
	void Init(const SParticleEmittInfo& info, const Camera* camera);

	//更新関数
	void Update()override;

	//座標を設定。
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_info.emitterPosition = position;
	}

private:
	const Camera*			m_pCamera;		//カメラ
	SParticleEmittInfo		m_info;			//パーティクルとエミッターの初期化情報
	float					m_lifeTimer;	//寿命
	float					m_intervalTime;	//パーティクルを出すインターバルタイム
	int						m_particleNum;	//1フレームに出るパーティクルの数
};