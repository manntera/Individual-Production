#pragma once
#include "Animation.h"

class Camera;
class SkinModelData;
class RenderContext;
class Light;
class Texture;

struct ShaderTechnique
{
	D3DXHANDLE NoSkinModelTechnique;		//�X�L������
	D3DXHANDLE SkinModelTechnique;			//�X�L���Ȃ�
};

//�V�F�[�_�[�e�N�j�b�N
enum EnSkinModelShaderTechnique
{
	enShaderTechniqueNormal,				//���ʂɕ`�悷��Ƃ��̃e�N�j�b�N
	enShaderTechniqueShadow,				//�e���������̃e�N�j�b�N
	enShaderTechniqueSilhouette,
	enShaderTechniqueNum,
};
class SkinModel : Uncopyable
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

	//�V���h�E�}�b�v�ɓo�^
	void ShadowMapEntry();


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

	//�@���}�b�v���Z�b�g
	void SetNormalMap(Texture* texture)
	{
		m_pNormalMap = texture;
		m_isHasNormalMap = true;
	}

	//�X�y�L�����}�b�v��ݒ�
	void SetSpecularMap(Texture* texture, Camera* camera)
	{
		m_pSpecularMap = texture;
		m_pCamera = camera;
		m_isHasSpecularMap = true;
	}

	/*
	�e�𗎂Ƃ�����ݒ�
	isShadowCaster		true�Ȃ�V���h�E�}�b�v�ɓo�^�Afalse�Ȃ�V���h�E�}�b�v����폜
	*/
	void SetShadowCasterFlg(bool isShadowCaster)
	{
		m_isShadowMapCaster = isShadowCaster;
	}

	/*
	�e�𗎂Ƃ���邩��ݒ�
	isShadowReceiver	true�Ȃ�e�𗎂Ƃ����Afalse�Ȃ�e�𗎂Ƃ��Ȃ�
	*/
	void SetShadowReceiverFlg(bool isShadowReceiver)
	{
		m_isShadowMapReceiver = isShadowReceiver;
	}

	/*
	�V�F�[�_�[�e�N�j�b�N��ݒ�
	shaderTechnique		�ݒ肷��V�F�[�_�[�e�N�j�b�N
	*/
	void SetShaderTechnique(EnSkinModelShaderTechnique shaderTechnique)
	{
		m_currentShaderTechnique = shaderTechnique;
	}

	//���̃V�F�[�_�[�e�N�j�b�N���擾
	EnSkinModelShaderTechnique GetCurrentShaderTechnique()
	{
		return m_currentShaderTechnique;
	}
private:
	bool						m_isShadowMapCaster;						//�e�𗎂Ƃ����H
	bool						m_isShadowMapReceiver;						//�e�𗎂Ƃ���邩�H
	ShaderTechnique				m_shaderTechnique[enShaderTechniqueNum];	//�V�F�[�_�[�e�N�j�b�N�̔z��
	EnSkinModelShaderTechnique	m_currentShaderTechnique;					//���݂̃V�F�[�_�[�e�N�j�b�N
	Texture*					m_pNormalMap;								//�@���}�b�v
	Texture*					m_pSpecularMap;								//�X�y�L�����}�b�v
	bool						m_isHasNormalMap;							//�@���}�b�v�������Ă��邩�H
	bool						m_isHasSpecularMap;							//�X�y�L�����}�b�v�������Ă��邩�H	
	D3DXMATRIX					m_worldMatrix;								//���[���h�s��
	D3DXMATRIX					m_rotationMatrix;							//��]�s��
	SkinModelData*				m_skinModelData;							//�X�L�����f���f�[�^
	ID3DXEffect*				m_pEffect;									//�G�t�F�N�g
	Animation					m_animation;								//�A�j���[�V����
	Light*						m_light;									//���C�g
	Camera*						m_pCamera;									//�X�y�L�����Ŏg���J����
	bool						m_isShadowCompesation;						//
};