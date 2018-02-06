#pragma once
#include "RenderTarget.h"
//�V���h�E�}�b�v�N���X

class SkinModel;

class ShadowMap : Uncopyable
{
public:
	//�R���X�g���N�^
	ShadowMap();

	//�f�X�g���N�^
	~ShadowMap();
	
	/*
	�V���h�E�}�b�v�����֐�
	width		�E�B���h�E�̕�
	height		�E�B���h�E�̍���
	*/
	void Create(int width, int height);

	/*
	�V���h�E�}�b�v�ɃG���g���[(���t���[�����Z�b�g����̂ł��̓s�x�G���g���[����K�v����
	model		�V���h�E�}�b�v�ɃG���g���[���郂�f��
	*/
	void Entry(SkinModel* model);

	//�X�V�֐�
	void Update();

	/*
	�V���h�E�}�b�v�ɕ`��
	*/
	void Draw();

	//�V���h�E�}�b�v�̃e�N�X�`�����擾
	const LPDIRECT3DTEXTURE9 GetShadowMapTexture() const;

	//���C�g�̒����_��ݒ�
	void SetLightCameraTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}

	//���W��ݒ�
	void SetLightCameraUp(D3DXVECTOR3 up)
	{
		m_up = up;
	}
	
	//���W��ݒ�
	void SetLightCameraPosition(D3DXVECTOR3 position)
	{
		m_position = position;
	}

	//���C�g�J�����̃r���[�s����擾
	const D3DXMATRIX& GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	//���C�g�J�����̃v���W�F�N�V�����s����擾
	const D3DXMATRIX& GetProjectionMatrix() const
	{
		return m_projMatrix;
	}
private:
	RenderTarget			m_renderTarget;		//�V���h�E�}�b�v
	D3DXVECTOR3				m_position;			//���C�g�̍��W
	D3DXVECTOR3				m_target;			//���C�g�̒����_
	D3DXVECTOR3				m_up;				//���C�g�̏����
	D3DXMATRIX				m_viewMatrix;		//���C�g�̃r���[�s��
	D3DXMATRIX				m_projMatrix;		//���C�g�̃v���W�F�N�V�����s��
	int						m_width;			//�E�B���h�E�̕�
	int						m_height;			//�E�B���h�E�̍���
	std::list<SkinModel*>	m_models;				//�V���h�E�}�b�v�ɕ`�悷�郂�f��
};