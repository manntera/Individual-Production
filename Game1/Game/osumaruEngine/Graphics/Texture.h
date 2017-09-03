#pragma once
//テクスチャのクラス
class Texture
{
public:
	Texture();

	~Texture();

	void Load(char* filePath);

	LPDIRECT3DTEXTURE9& GetBody()
	{
		return m_pTexture;
	}


	int GetWidth()
	{
		return m_srcInfo.Width;
	}

	int GetHeight()
	{
		return m_srcInfo.Height;
	}
	
	void Release();

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_srcInfo;
};