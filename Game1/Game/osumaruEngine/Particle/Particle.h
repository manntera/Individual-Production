#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Texture.h"
class Camera;
struct SParticleEmittInfo;

//�p�[�e�B�N��
class Particle : public GameObject
{
public:

	//�R���X�g���N�^
	Particle();

	//�f�X�g���N�^
	~Particle();

	/*
	�p�[�e�B�N����������
	info	�p�[�e�B�N���̏��������
	camera	�r���{�[�h�����Ɏg���J����
	*/
	void Init(SParticleEmittInfo& info, Camera* camera);

	//�X�V�֐�
	void Update()override;

	//�`�揈��
	void AfterDraw()override;

private:
	D3DXVECTOR2		m_size;			//�T�C�Y
	Texture*		m_texture;		//�e�N�X�`��
	Primitive		m_primitive;	//�v���~�e�B�u
	D3DXMATRIX		m_worldMatrix;	//���[���h�s��
	D3DXQUATERNION	m_rotation;		//��]
	LPD3DXEFFECT	m_pEffect;		//�G�t�F�N�g
	D3DXVECTOR3		m_position;		//���W
	Camera*			m_camera;		//�J����
	float			m_lifeTimer;	//����
	float			m_angle;		//��]��
};