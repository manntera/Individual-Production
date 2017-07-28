#include "EffectManager.h"

int MakeHash(const char* string)
{
	int hash = 0;
	int len = strlen(string);
	for (int i = 0;i < len;i++)
	{
		hash = hash * 37 + string[i];
	}
	return hash;
}


EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{
	Release();
}

LPD3DXEFFECT EffectManager::LoadEffect(const char* filePath)
{
	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);
	auto it = effectDictionary.find(hash);
	if (it == effectDictionary.end())
	{
		LPD3DXBUFFER compileErrorBuffer = nullptr;
		HRESULT hr = D3DXCreateEffectFromFile(
			g_pD3DDevice,
			filePath,
			NULL,
			NULL,
#ifdef _DEBUG
			D3DXSHADER_DEBUG,
#else
			D3DXSHADER_SKIPVALIDATION,
#endif
			NULL,
			&effect,
			&compileErrorBuffer);
		if (FAILED(hr))
		{
			MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			//“Ç‚Ýž‚ÝŽ¸”s
			std::abort();
		}
		effectDictionary.insert({ hash, effect });
	}
	else
	{
		//“o˜^Ï‚Ý
		effect = it->second;
	}
	return effect;
}

void EffectManager::Release()
{
	for (auto it : effectDictionary)
	{
		it.second->Release();
	}
	effectDictionary.clear();
}