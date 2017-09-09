#pragma once

//エフェクトを読み込んで保持するクラス

class EffectManager
{
public:
	//コンストラクタ
	EffectManager();

	~EffectManager();

	/*
	エフェクトのロード
	読み込み済みのエフェクトはロードせずに既存のエフェクトが返ってくる
	filePath		読み込むファイルのパス。
	*/
	LPD3DXEFFECT LoadEffect(const char* filePath);

	//ハッシュ値を文字列からintの値で作る関数
	int MakeHash(const char* string);

	//リリース
	void Release();
private:
	std::map<int, LPD3DXEFFECT> effectDictionary;	//エフェクトをファイルパスのハッシュ値をキーに持つ。
};