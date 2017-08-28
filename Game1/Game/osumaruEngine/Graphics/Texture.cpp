#include "Texture.h"
#include "../Engine.h"

Texture::Texture()
{
	m_pTexture = nullptr;
}

Texture::~Texture()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		delete m_pTexture;
	}
}

void Texture::Load(char *filePath)
{
	D3DXCreateTextureFromFileEx(
		GetEngine().GetDevice(),
		filePath,
		0,
		0,
		0,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&m_srcInfo,
		NULL,
		&m_pTexture
	);
}