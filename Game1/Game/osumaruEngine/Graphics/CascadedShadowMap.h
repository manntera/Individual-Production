#pragma once
class SkinModel;
class Camera;

class CascadedShadowMap
{
public:
	//�R���X�g���N�^
	CascadedShadowMap();

	//�f�X�g���N�^
	~CascadedShadowMap();

	void Init(int width, int height, float lightHeight);

	void Update();

	void Draw();

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
		m_isActive = true;
	}

	const D3DXMATRIX& GetViewMatrix(int index) const
	{
		return m_viewMatrix[index];
	}

	const D3DXMATRIX& GetProjectionMatrix(int index) const
	{
		return m_projMatrix[index];
	}

	void Entry(SkinModel* model)
	{
		m_models.push_back(model);
	}

	void SetUp(D3DXVECTOR3 up)
	{
		m_up = up;
	}

	void SetTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}
private:
	static const int		SHADOWMAP_NUM = 3;
	RenderTarget			m_renderTarget[SHADOWMAP_NUM];		//�V���h�E�}�b�v
	D3DXVECTOR3				m_target;			//���C�g�̕���
	D3DXVECTOR3				m_up;				//���C�g�̏����
	D3DXMATRIX				m_viewMatrix[SHADOWMAP_NUM];		//���C�g�̃r���[�s��
	D3DXMATRIX				m_projMatrix[SHADOWMAP_NUM];		//���C�g�̃v���W�F�N�V�����s��
	int						m_width;			//�E�B���h�E�̕�
	int						m_height;			//�E�B���h�E�̍���
	std::list<SkinModel*>	m_models;			//�V���h�E�}�b�v�ɕ`�悷�郂�f��
	Camera*					m_pCamera;
	bool					m_isActive;
	float m_lightHeight;
};