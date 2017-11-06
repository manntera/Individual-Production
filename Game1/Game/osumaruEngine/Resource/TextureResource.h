#pragma once
class Texture;

class TextureResource : Uncopyable
{
public:
	TextureResource();

	~TextureResource();

	Texture* LoadTexture(char* filePath);


private:
	std::map<char*, Texture*> m_textures;
};