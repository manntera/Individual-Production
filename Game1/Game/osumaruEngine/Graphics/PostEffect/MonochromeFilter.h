#pragma once
//���m�N���t�B���^�[

class MonochromeFilter
{
public:
	//�R���X�g���N�^
	MonochromeFilter();

	//�f�X�g���N�^
	~MonochromeFilter();

	/*
	�������֐�
	isActive	�A�N�e�B�u���H
	*/
	void Init(bool isActive);

	//�`��֐�
	void Draw();

	//�A�N�e�B�u�ɂ��邩��ݒ�
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

	//�A���t�@�l��ݒ�
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

private:
	Primitive		m_primitive;	//�v���~�e�B�u
	LPD3DXEFFECT	m_pEffect;		//�G�t�F�N�g
	bool			m_isActive;		//�A�N�e�B�u���H
	float			m_alpha;		//�A���t�@�l
};