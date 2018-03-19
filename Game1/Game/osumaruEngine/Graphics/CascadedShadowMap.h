#pragma once
class SkinModel;
class Camera;
//�J�X�P�[�h�V���h�E�}�b�v

class CascadedShadowMap
{
public:
	//�R���X�g���N�^
	CascadedShadowMap();

	//�f�X�g���N�^
	~CascadedShadowMap();
	
	/*
	������
	width			�e�N�X�`���̕�
	height			�e�N�X�`���̏c��
	lightHeight		���C�g�J�����̍���
	*/
	void Init(int width, int height, float lightHeight);

	//�X�V
	void Update();

	//�`��
	void Draw();

	/*
	�V���h�E�}�b�v�̃e�N�X�`�����擾
	textureNum	�e�N�X�`���̔z��̃C���f�b�N�X
	*/
	const LPDIRECT3DTEXTURE9 GetShadowMapTexture(int textureNum) const
	{
		return m_renderTarget[textureNum].GetTexture();
	}

	//���C�g�̒����_��ݒ�
	void SetLightCameraTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}

	//���W��ݒ�
	void SetLightCameraUp(const D3DXVECTOR3& up)
	{
		m_up = up;
	}

	//�Q�[���Ŏg���Ă���J�����̐ݒ�
	void SetGameCamera(Camera* camera)
	{
		m_pCamera = camera;
		if (m_pCamera != nullptr)
		{
			m_isActive = true;
		}
		else
		{
			m_isActive = false;
		}
	}

	/*
	�r���[�s����擾
	index	�z��̃C���f�b�N�X
	*/
	const D3DXMATRIX& GetViewMatrix(int index) const
	{
		return m_viewMatrix[index];
	}
	/*
	�v���W�F�N�V�����s����擾
	index	�z��̃C���f�b�N�X
	*/
	const D3DXMATRIX& GetProjectionMatrix(int index) const
	{
		return m_projMatrix[index];
	}

	/*
	�V���h�E�}�b�v�ɕ`�悷�郂�f����o�^
	model	�o�^���郂�f��
	*/
	void Entry(SkinModel* model)
	{
		m_models.push_back(model);
	}

	//���C�g�J�����̏����������
	void SetUp(D3DXVECTOR3 up)
	{
		m_up = up;
	}

	//���C�g�J�����̒����_��ݒ�
	void SetTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}

	int GetShadowMapNum() const
	{
		return SHADOWMAP_NUM;
	}
private:
	static const int		SHADOWMAP_NUM = 3;					//�V���h�E�}�b�v�̐�
	RenderTarget			m_renderTarget[SHADOWMAP_NUM];		//�V���h�E�}�b�v
	D3DXVECTOR3				m_target;							//���C�g�̕���
	D3DXVECTOR3				m_up;								//���C�g�̏����
	D3DXMATRIX				m_viewMatrix[SHADOWMAP_NUM];		//���C�g�̃r���[�s��
	D3DXMATRIX				m_projMatrix[SHADOWMAP_NUM];		//���C�g�̃v���W�F�N�V�����s��
	int						m_width;							//�E�B���h�E�̕�
	int						m_height;							//�E�B���h�E�̍���
	std::list<SkinModel*>	m_models;							//�V���h�E�}�b�v�ɕ`�悷�郂�f��
	Camera*					m_pCamera;							//���C���̃J����
	bool					m_isActive;							//�A�N�e�B�u���H
	float					m_lightHeight;						//���C�g�J�����̍���
};