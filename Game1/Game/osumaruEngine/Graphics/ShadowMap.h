#pragma once
//�V���h�E�}�b�v�N���X

class SkinModel;

class ShadowMap
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
	LPDIRECT3DTEXTURE9 GetShadowMapTexture();

	void SetTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}

	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
	}

	D3DXMATRIX GetViewMatrix()
	{
		return m_viewMatrix;
	}

	D3DXMATRIX GetProjMatrix()
	{
		return m_projMatrix;
	}
	
	void Release();


private:
	LPDIRECT3DTEXTURE9		m_pShadowMap;
	D3DXVECTOR3				m_position;
	D3DXVECTOR3				m_target;
	D3DXVECTOR3				m_up;
	D3DXMATRIX				m_viewMatrix;
	D3DXMATRIX				m_projMatrix;
	int						m_width;
	int						m_height;
	std::vector<SkinModel*> m_models;
};