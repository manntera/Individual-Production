#pragma once
#include "Animation.h"

class SkinModelData;
class RenderContext;
class Light;

class SkinModel
{
public:
	//�R���X�g���N�^
	SkinModel();

	//�f�X�g���N�^
	~SkinModel();

	/*
	�������֐�
	modelData		���f����ǂݍ��񂾃f�[�^
	*/
	void Init(SkinModelData* modelData);

	/*
	�`��֐�
	viewMatrix		�J�����̃r���[�s��
	projMatrix		�J�����̃v���W�F�N�V�����s��
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);

	/*
	���[���h�s����X�V�B
	trans	���s�ړ�
	rot		��]
	scale	�g��
	*/
	void UpdateWorldMatrix(D3DXVECTOR3 trans, D3DXQUATERNION rot, D3DXVECTOR3 scale);

	/*
	���C�g��ݒ�
	*/
	void SetLight(Light *light)
	{
		this->m_light = light;
	}

	//���[���h�s����擾�B
	D3DXMATRIX GetWorldMatrix()
	{
		return m_worldMatrix;
	}
	/*
	�I���W�i�����b�V���̐擪���擾����
	*/
	LPD3DXMESH GetOrgMeshFirst();

private:
	D3DXMATRIX		m_worldMatrix;				//���[���h�s��
	D3DXMATRIX		m_rotationMatrix;				//��]�s��
	SkinModelData*	m_skinModelData;				//�X�L�����f���f�[�^
	ID3DXEffect*	m_pEffect;					//�G�t�F�N�g
	Animation		m_animation;					//�A�j���[�V����
	Light*			m_light;						//���C�g
};