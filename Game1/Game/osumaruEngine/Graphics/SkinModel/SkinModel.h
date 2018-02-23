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
	enShaderTechniqueDithering,
	enShaderTechniqueGhost,
	enShaderTechniquePlayer,
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
	void Draw(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

	/*
	���[���h�s����X�V�B
	trans	���s�ړ�
	rot		��]
	scale	�g��
	*/
	void UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	/*
	�X�V�B
	trans	���s�ړ�
	rot		��]
	scale	�g��
	*/
	void Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	//�V���h�E�}�b�v�ɓo�^
	void ShadowMapEntry();


	/*
	���C�g��ݒ�
	*/
	void SetLight(const Light *light)
	{
		this->m_pLight = light;
	}

	//���[���h�s����擾�B
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}
	/*
	�I���W�i�����b�V���̐擪���擾����
	*/
	const LPD3DXMESH GetOrgMeshFirst() const;

	//�@���}�b�v���Z�b�g
	void SetNormalMap(const Texture* texture)
	{
		m_pNormalMap = texture;
		m_isHasNormalMap = true;
	}

	//�X�y�L�����}�b�v��ݒ�
	void SetSpecularMap(const Texture* texture, const Camera* camera)
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
	EnSkinModelShaderTechnique GetCurrentShaderTechnique() const
	{
		return m_currentShaderTechnique;
	}

	//�n�ʂɐ����ȕ��������郂�f�����̃t���O��ݒ�
	void SetShadowCompesationFlg(bool isShadowCompesation)
	{
		m_isShadowCompesation = isShadowCompesation;
	}

	//�n�ʂɐ����ȕ��������郂�f�����H
	bool IsShadowCompesation() const
	{
		return m_isShadowCompesation;
	}


	//���W�̎擾�B
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}

	//�X�P�[���̎擾�B
	const D3DXVECTOR3& GetScale() const
	{
		return m_scale;
	}

	//��]���擾�B
	const D3DXQUATERNION& GetRotation() const
	{
		return m_rotation;
	}


private:
	bool						m_isShadowMapCaster;						//�e�𗎂Ƃ����H
	bool						m_isShadowMapReceiver;						//�e�𗎂Ƃ���邩�H
	ShaderTechnique				m_shaderTechnique[enShaderTechniqueNum];	//�V�F�[�_�[�e�N�j�b�N�̔z��
	EnSkinModelShaderTechnique	m_currentShaderTechnique;					//���݂̃V�F�[�_�[�e�N�j�b�N
	const Texture*				m_pNormalMap;								//�@���}�b�v
	const Texture*				m_pSpecularMap;								//�X�y�L�����}�b�v
	bool						m_isHasNormalMap;							//�@���}�b�v�������Ă��邩�H
	bool						m_isHasSpecularMap;							//�X�y�L�����}�b�v�������Ă��邩�H	
	D3DXMATRIX					m_worldMatrix;								//���[���h�s��
	D3DXMATRIX					m_rotationMatrix;							//��]�s��
	SkinModelData*				m_pSkinModelData;							//�X�L�����f���f�[�^
	ID3DXEffect*				m_pEffect;									//�G�t�F�N�g
	Animation					m_animation;								//�A�j���[�V����
	const Light*				m_pLight;									//���C�g
	const Camera*				m_pCamera;									//�X�y�L�����Ŏg���J����
	bool						m_isShadowCompesation;						//�n�ʂɐ����ȕ����ɗ�����e�̕␳���邩�H
	D3DXVECTOR3					m_position;									//���f���̍��W
	D3DXVECTOR3					m_scale;									//���f���̃X�P�[��
	D3DXQUATERNION				m_rotation;									//���f���̉�]
	bool						m_isShadowEntry;							//�V���h�E�}�b�v�ɓo�^����Ă��邩�H
	float						m_ditheringRate;							//�f�B�U�����O�̓����x
};