#pragma once

class Light
{
public:
	static const int	DIFFUSE_LIGHT_NUM = 4;	//���s�����̐��B
public:
	//�R���X�g���N�^
	Light() :
		m_diffuseLightDirection{},
		m_diffuseLightColor{},
		m_ambientLight(0.0f, 0.0f, 0.0f, 0.0f)
	{
		for (int i = 0;i < DIFFUSE_LIGHT_NUM;i++)
		{
			m_diffuseLightColor[i] = { 0.0f, 0.0f, 0.0f, 1.0f };
			m_diffuseLightDirection[i] = { 1.0f, 0.0f, 0.0f, 1.0f };
		}
	}

	//�f�X�g���N�^
	~Light()
	{

	}

	//���s�����̕������擾�B
	const D3DXVECTOR4* GetDiffuseLightDirection() const
	{
		return m_diffuseLightDirection;
	}

	//���s�����̐F���擾�B
	const D3DXVECTOR4* GetDiffuseLightColor() const
	{
		return m_diffuseLightColor;
	}

	/*
	���s�����̕�����ݒ�B
	lightNo		���C�g�̔ԍ�
	dir			�����B
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}


	/*
	���s�����̐F��ݒ�
	lightNo		���C�g�̔ԍ�
	color		�F
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}

	/*
	�A���r�G���g���C�g��ݒ�B
	ambient		�F
	*/
	void SetAmbiemtLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}

	//�A���r�G���g���C�g���擾�B
	const D3DXVECTOR4& GetAmbientLight() const
	{
		return m_ambientLight;
	}
private:
	D3DXVECTOR4			m_diffuseLightDirection[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̕���
	D3DXVECTOR4			m_diffuseLightColor[DIFFUSE_LIGHT_NUM];			//�f�B�t���[�Y���C�g�̐F
	D3DXVECTOR4			m_ambientLight;									//�A���r�G���g�̐F
};