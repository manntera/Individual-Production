#pragma once
//�e�N�X�`���N���X

class Texture : Uncopyable
{
public:
	//�R���X�g���N�^
	Texture();

	//�f�X�g���N�^
	~Texture();

	/*
	�e�N�X�`���̃��[�h
	filePath	�ǂݍ��ރe�N�X�`���̃t�@�C���p�X
	*/
	void Load(char* filePath);

	//�e�N�X�`�����擾�B
	const LPDIRECT3DTEXTURE9& GetBody() const
	{
		return m_pTexture;
	}

	//�e�N�X�`���̕����擾�B
	int GetWidth() const
	{
		return m_srcInfo.Width;
	}

	//�e�N�X�`���̍������擾�B
	int GetHeight() const
	{
		return m_srcInfo.Height;
	}
	
	//�����[�X
	void Release();

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DXIMAGE_INFO m_srcInfo;		//�e�N�X�`���̏��
};