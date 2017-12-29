#include "engineStdafx.h"
#include "TextureResource.h"
#include "../Graphics/Texture.h"

TextureResource::TextureResource()
{

}

TextureResource::~TextureResource()
{
	for (auto& map : m_textures)
	{
		delete map.second;
	}
}

Texture* TextureResource::LoadTexture(char* filePath)
{
	int hash = MakeHash(filePath);
	auto& map = m_textures.find(hash);
	if (map == m_textures.end())
	{
		Texture* texture = new Texture;
		texture->Load(filePath);
		m_textures.insert({ hash, texture });
		return texture;
	}
	else
	{
		return map->second;
	}
}