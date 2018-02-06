#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Texture.h"
class Camera;
struct SParticleEmittInfo;

//パーティクル
class Particle : public GameObject
{
public:

	//コンストラクタ
	Particle();

	//デストラクタ
	~Particle();

	/*
	パーティクルを初期化
	info	パーティクルの初期化情報
	camera	ビルボード処理に使うカメラ
	*/
	void Init(SParticleEmittInfo& info, const Camera* camera);

	//更新関数
	void Update()override;

	//描画処理
	void Draw()override;

private:
	D3DXVECTOR2		m_size;			//サイズ
	Texture*		m_pTexture;		//テクスチャ
	Primitive		m_primitive;	//プリミティブ
	D3DXMATRIX		m_worldMatrix;	//ワールド行列
	D3DXQUATERNION	m_rotation;		//回転
	LPD3DXEFFECT	m_pEffect;		//エフェクト
	D3DXVECTOR3		m_position;		//座標
	const Camera*	m_camera;		//カメラ
	float			m_lifeTimer;	//寿命
	float			m_angle;		//回転量
	D3DXVECTOR3		m_gravity;		//重力
	D3DXVECTOR3		m_speed;		//速度
};