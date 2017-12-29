#pragma once
class Texture;
//テクスチャのリソース管理クラス

class TextureResource : Uncopyable
{
public:
	//コンストラクタ
	TextureResource();

	//デストラクタ
	~TextureResource();

	//テクスチャを取得
	Texture* LoadTexture(char* filePath);
private:
	std::map<int, Texture*> m_textures;	//テクスチャ
};