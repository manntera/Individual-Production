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
	float	lifeTime;			//パーティクルの寿命
	float	emittIntervalTime;	//パーティクルが出るインターバルの時間
	float	emitterLifeTime;	//エミッターの寿命
	D3DXVECTOR3 emitterPosition;//エミッターの座標
};

class ParticleEmitter : public GameObject
{
public:
	ParticleEmitter();

	~ParticleEmitter();

	void Init(SParticleEmittInfo info, Camera* camera);

	void Update()override;

	void SetPosition(D3DXVECTOR3 position)
	{
		m_info.emitterPosition = position;
	}

private:
	Camera*					m_camera;
	SParticleEmittInfo		m_info;
	float					m_lifeTimer;
	float					m_intervalTime;
};