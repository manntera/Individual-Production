#include "engineStdafx.h"
#include "EffectManager.h"
#include "../Engine.h"



EffectManager::EffectManager() :
	m_effectDictionary()
{

}

EffectManager::~EffectManager()
{
	Release();
}

LPD3DXEFFECT EffectManager::LoadEffect(char* filePath)
{
	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);
	auto it = m_effectDictionary.find(hash);
	if (it == m_effectDictionary.end())
	{
		LPD3DXBUFFER compileErrorBuffer = nullptr;
		HRESULT hr = D3DXCreateEffectFromFile(
			GetEngine().GetDevice(),
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
		m_effectDictionary.insert({ hash, effect });
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
	for (auto it : m_effectDictionary)
	{
		it.second->Release();
	}
	m_effectDictionary.clear();
}