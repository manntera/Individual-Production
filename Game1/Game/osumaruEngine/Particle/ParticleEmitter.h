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
	D3DXVECTOR3 randomPosition;		//�p�[�e�B�N�����W�̃����_����
	D3DXVECTOR3 gravity;		//�p�[�e�B�N���̏d��
	float	lifeTime;			//�p�[�e�B�N���̎���
	float	emittIntervalTime;	//�p�[�e�B�N�����o��C���^�[�o���̎���
	float	emitterLifeTime;	//�G�~�b�^�[�̎���
	D3DXVECTOR3 emitterPosition;//�G�~�b�^�[�̍��W
	int particleNum;			//�����ɏo��p�[�e�B�N���̐�
	bool isFirstTimeRandom;		//��ԍŏ��Ƀp�[�e�B�N���o���Ƃ��������Ԃ����炷��
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
	void Init(const SParticleEmittInfo& info, const Camera* camera);

	//�X�V�֐�
	void Update()override;

	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_info.emitterPosition = position;
	}

private:
	const Camera*			m_pCamera;		//�J����
	SParticleEmittInfo		m_info;			//�p�[�e�B�N���ƃG�~�b�^�[�̏��������
	float					m_lifeTimer;	//����
	float					m_intervalTime;	//�p�[�e�B�N�����o���C���^�[�o���^�C��
	int						m_particleNum;	//1�t���[���ɏo��p�[�e�B�N���̐�
};