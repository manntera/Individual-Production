#pragma once
#include "../common.h"

class EffectManager
{
public:

	EffectManager();

	~EffectManager();

	/*
	エフェクトのロード
	読み込み済みのエフェクトはロードせずに既存のエフェクトが返ってくる
	*/
	ID3DXEffect* LoadEffect(const char* filePath);

	void Release();
private:
	std::map<int, ID3DXEffect*> effectDictionary;
};