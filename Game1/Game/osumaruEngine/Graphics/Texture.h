#pragma once
//テクスチャクラス

class Texture : Uncopyable
{
public:
	//コンストラクタ
	Texture();

	//デストラクタ
	~Texture();

	/*
	テクスチャのロード
	filePath	読み込むテクスチャのファイルパス
	*/
	void Load(char* filePath);

	//テクスチャを取得。
	LPDIRECT3DTEXTURE9& GetBody()
	{
		return m_pTexture;
	}

	//テクスチャの幅を取得。
	int GetWidth()
	{
		return m_srcInfo.Width;
	}

	//テクスチャの高さを取得。
	int GetHeight()
	{
		return m_srcInfo.Height;
	}
	
	//リリース
	void Release();

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	D3DXIMAGE_INFO m_srcInfo;		//テクスチャの情報
};