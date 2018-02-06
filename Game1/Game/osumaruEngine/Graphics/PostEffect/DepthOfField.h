#pragma once
//��ʊE�[�x�̃N���X

class DepthOfField : Uncopyable
{
public:
	//�R���X�g���N�^
	DepthOfField();

	//�f�X�g���N�^
	~DepthOfField();

	/*
	�������֐�
	isActive �A�N�e�B�u���H
	*/
	void Init(bool isActive);

	//�`��֐�
	void Draw();

	//�[�x�l�������ݗp�̃����_�����O�^�[�Q�b�g���擾
	const RenderTarget& GetDepthRendertarget() const
	{
		return m_depthTarget;
	}

private:
	const static int	BLUR_RANGE = 8;			//�u���[��������s�N�Z���͈̔�
	bool				m_isActive;				//�A�N�e�B�u���H
	RenderTarget		m_depthTarget;			//�[�x�������ݗp�̃����_�����O�^�[�Q�b�g
	RenderTarget		m_blur[2];				//�u���[��������ڂ����p�̃����_�����O�^�[�Q�b�g
	float				m_weight[BLUR_RANGE];	//�K�E�X�u���[�̃E�F�C�g
	LPD3DXEFFECT		m_pEffect;				//�G�t�F�N�g
	Primitive			m_primitive;			//�v���~�e�B�u
};
