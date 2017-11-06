#pragma once
class Particle;
class Camera;
#include "../Graphics/Texture.h"

struct SParticleEmittInfo
{
	char*	filePath;			//�e�N�X�`���̃t�@�C���p�X
	float width;				//�p�[�e�B�N���̉���
	float height;				//�p�[�e�B�N���̏c��
	D3DXVECTOR4 uv;				//�e�N�X�`����uv���W�B�����uv�A�E����uv
	float	lifeTime;			//�p�[�e�B�N���̎���
	float	emittIntervalTime;	//�p�[�e�B�N�����o��C���^�[�o���̎���
	float	emitterLifeTime;	//�G�~�b�^�[�̎���
	D3DXVECTOR3 emitterPosition;//�G�~�b�^�[�̍��W
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