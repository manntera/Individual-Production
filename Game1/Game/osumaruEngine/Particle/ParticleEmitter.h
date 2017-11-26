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

//�p�[�e�B�N���G�~�b�^�[
class ParticleEmitter : public GameObject
{
public:
	//�R���X�g���N�^
	ParticleEmitter();

	//�f�X�g���N�^
	~ParticleEmitter();

	/*
	�G�~�b�^�[�̏�����
	info�@�p�[�e�B�N���ƃG�~�b�^�[�̏��������
	camera	�r���{�[�h�����Ɏg���J����
	*/
	void Init(SParticleEmittInfo info, Camera* camera);

	//�X�V�֐�
	void Update()override;

	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 position)
	{
		m_info.emitterPosition = position;
	}

private:
	Camera*					m_camera;		//�J����
	SParticleEmittInfo		m_info;			//�p�[�e�B�N���ƃG�~�b�^�[�̏��������
	float					m_lifeTimer;	//����
	float					m_intervalTime;	//�p�[�e�B�N�����o���C���^�[�o���^�C��
};