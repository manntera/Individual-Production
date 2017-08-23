//#pragma once
//#include "Animation.h"
//
//class SkinModelData;
//class RenderContext;
//class Light;
//
//class SkinModel
//{
//public:
//
//	SkinModel();
//
//	~SkinModel();
//
//	//������
//	void Init(SkinModelData* modelData);
//
//	void Draw(D3DXMATRIX* viewmatrix, D3DXMATRIX* projMatrix);
//
//	/*
//	���[���h�s����X�V�B
//	trans	���s�ړ�
//	rot		��]
//	scale	�g��
//	*/
//	void UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);
//
//	/*
//	���C�g��ݒ�
//	*/
//	void SetLight(Light *light)
//	{
//		this->light = = light;
//	}
//	/*
//	�I���W�i�����b�V���̐擪���擾����
//	*/
//
//private:
//	D3DXMATRIX		worldMatrix;				//���[���h�s��
//	D3DXMATRIX		rotationMatrix;				//��]�s��
//	SkinModelData*	skinModelData;				//�X�L�����f���f�[�^
//	ID3DXEffect*	pEffect;					//�G�t�F�N�g
//	Animation		animation;					//�A�j���[�V����
//	Light*			light;						//���C�g
//};