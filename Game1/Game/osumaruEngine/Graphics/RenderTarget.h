#pragma once

class RenderTarget
{
public:
	//�R���X�g���N�^
	RenderTarget();

	//�f�X�g���N�^
	~RenderTarget();
	
	/*
	�����_�[�^�[�Q�b�g���쐬
	width		�e�N�X�`���̕�
	height		�e�N�X�`���̍���
	format		�e�N�X�`���̃t�H�[�}�b�g
	depthFormat	�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	*/
	void Create(int width, int height, D3DFORMAT format, D3DFORMAT depthFormat);

	//�e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_pTexture;
	}

	//�����_�[�^�[�Q�b�g���擾
	LPDIRECT3DSURFACE9 GetRenderTarget()
	{
		return m_pRenderTarget;
	}

	//�[�x�X�e���V���o�b�t�@���擾
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}

	//�������
	void Release();


private:
	LPDIRECT3DTEXTURE9		m_pTexture;			//�e�N�X�`��
	LPDIRECT3DSURFACE9		m_pDepthBuffer;		//�[�x�X�e���V���o�b�t�@
	LPDIRECT3DSURFACE9		m_pRenderTarget;	//�����_�����O�^�[�Q�b�g
};