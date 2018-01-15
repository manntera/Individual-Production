#pragma once
//�u���[���N���X

class Bloom : Uncopyable
{
public:
	//�R���X�g���N�^
	Bloom();

	//�f�X�g���N�^
	~Bloom();

	/*
	�������֐�
	isActive	�A�N�e�B�u���H
	*/
	void Init(bool isActive);

	//�`��֐�
	void Draw();

	//�K�E�X�u���[�̃E�F�C�g��ݒ�
	void SetWeight(float rate);
private:
	const static int BLUR_RANGE = 8;							//�u���[��������s�N�Z���͈̔�
	const static int DOWN_SAMPLING_NUM = 5;						//�_�E���T���v�����O
	RenderTarget m_downSamplingTarget[DOWN_SAMPLING_NUM][2];	//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g
	RenderTarget m_luminanceTarget;								//�P�x���o�p�̃����_�����O�^�[�Q�b�g
	RenderTarget m_combineTarget;								//�ŏI�I�ɍ�������悤�̃����_�����O�^�[�Q�b�g
	LPD3DXEFFECT m_pEffect;										//�G�t�F�N�g
	float		 m_weight[BLUR_RANGE];							//�K�E�X�u���[�̃E�F�C�g
	Primitive	 m_primitive;									//�v���~�e�B�u
	bool		 m_isActive;									//�A�N�e�B�u���H
};