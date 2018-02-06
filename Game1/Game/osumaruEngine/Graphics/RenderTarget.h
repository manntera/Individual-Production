#pragma once

class RenderTarget : Uncopyable
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
	const LPDIRECT3DTEXTURE9 GetTexture() const
	{
		return m_pTexture;
	}

	//�����_�[�^�[�Q�b�g���擾
	const LPDIRECT3DSURFACE9 GetRenderTarget() const
	{
		return m_pRenderTarget;
	}

	//�[�x�X�e���V���o�b�t�@���擾
	const LPDIRECT3DSURFACE9 GetDepthStencilBuffer() const
	{
		return m_pDepthBuffer;
	}

	//�e�N�X�`���̕����擾
	int GetWidth() const
	{
		return m_width;
	}

	//�e�N�X�`���̍������擾�B
	int GetHeight() const
	{
		return m_height;
	}

	//�������
	void Release();


private:
	LPDIRECT3DTEXTURE9		m_pTexture;			//�e�N�X�`��
	LPDIRECT3DSURFACE9		m_pDepthBuffer;		//�[�x�X�e���V���o�b�t�@
	LPDIRECT3DSURFACE9		m_pRenderTarget;	//�����_�����O�^�[�Q�b�g
	int						m_width;			//�e�N�X�`���̕�
	int						m_height;			//�e�N�X�`���̍���
};