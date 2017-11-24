#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Texture.h"
class Camera;
struct SParticleEmittInfo;

class Particle : public GameObject
{
public:

	Particle();

	~Particle();

	void Init(SParticleEmittInfo& info, Camera* camera);

	void Update()override;

	void AfterDraw()override;

private:
	D3DXVECTOR2		m_size;
	Texture*		m_texture;
	Primitive		m_primitive;
	D3DXMATRIX		m_worldMatrix;
	D3DXQUATERNION	m_rotation;
	LPD3DXEFFECT	m_pEffect;
	D3DXVECTOR3		m_position;
	Camera*			m_camera;
	float			m_lifeTimer;
	float			m_angle;
};