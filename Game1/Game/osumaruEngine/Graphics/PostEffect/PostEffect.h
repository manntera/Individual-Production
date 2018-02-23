#pragma once
#include "MonochromeFilter.h"
#include "Bloom.h"
#include "DepthOfField.h"
//�|�X�g�G�t�F�N�g

class PostEffect
{
public:
	//�R���X�g���N�^
	PostEffect();

	//�f�X�g���N�^
	~PostEffect();

	//�������֐�
	void Init();

	//�`��֐�
	void Draw();

	//��ʊE�[�x���擾
	const DepthOfField& GetDepthOfField() const
	{
		return m_dof;
	}

private:
	Bloom				m_bloom;		//�u���[��
	MonochromeFilter	m_monochrome;	//���m�N���t�B���^�[
	DepthOfField		m_dof;			//��ʊE�[�x
	Primitive			m_primitive;	//�v���~�e�B�u
	LPD3DXEFFECT		m_pEffect;		//�G�t�F�N�g
	LPDIRECT3DSURFACE9	m_frameBuffer;	//�o�b�N�o�b�t�@
	LPDIRECT3DSURFACE9	m_depthBuffer;	//�f�v�X�X�e���V���o�b�t�@
};