#pragma once

class EffectManager
{
public:

	EffectManager();

	~EffectManager();

	/*
	エフェクトのロード
	読み込み済みのエフェクトはロードせずに既存のエフェクトが返ってくる
	*/
	LPD3DXEFFECT LoadEffect(const char* filePath);

	void Release();
private:
	std::map<int, LPD3DXEFFECT> effectDictionary;
};