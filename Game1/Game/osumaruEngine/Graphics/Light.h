#pragma once

class Light
{
public:
	static const int	DIFFUSE_LIGHT_NUM = 4;	//���s�����̐��B
public:
	//�R���X�g���N�^
	Light()
	{
		memset(this, 0, sizeof(Light));
	}

	//�f�X�g���N�^
	~Light()
	{

	}

	//���s�����̕������擾�B
	const D3DXVECTOR4* GetDiffuseLightDirection() const
	{
		return diffuseLightDirection;
	}

	//���s�����̐F���擾�B
	const D3DXVECTOR4* GetDiffuseLightColor() const
	{
		return diffuseLightColor;
	}

	/*
	���s�����̕�����ݒ�B
	lightNo		���C�g�̔ԍ�
	dir			�����B
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		diffuseLightDirection[lightNo] = dir;
	}


	/*
	���s�����̐F��ݒ�
	lightNo		���C�g�̔ԍ�
	color		�F
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		diffuseLightColor[lightNo] = color;
	}

	/*
	�A���r�G���g���C�g��ݒ�B
	ambient		�F
	*/
	void SetAmbiemtLight(const D3DXVECTOR4& ambient)
	{
		ambientLight = ambient;
	}

	//�A���r�G���g���C�g���擾�B
	D3DXVECTOR4 GetAmbientLight()
	{
		return ambientLight;
	}
private:
	D3DXVECTOR4			diffuseLightDirection[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̕���
	D3DXVECTOR4			diffuseLightColor[DIFFUSE_LIGHT_NUM];			//�f�B�t���[�Y���C�g�̐F
	D3DXVECTOR4			ambientLight;									//�A���r�G���g�̐F
};