#pragma once

//エフェクトを読み込んで保持するクラス

class EffectManager
{
public:
	//コンストラクタ
	EffectManager();

	//デストラクタ
	~EffectManager();

	/*
	エフェクトのロード
	読み込み済みのエフェクトはロードせずに既存のエフェクトが返ってくる
	filePath		読み込むファイルのパス。
	return			読み込んだエフェクト
	*/
	LPD3DXEFFECT LoadEffect(char* filePath);

	//ハッシュ値を文字列からintの値で作る関数
	int MakeHash(char* string);

	//リリース
	void Release();
private:
	std::map<int, LPD3DXEFFECT> m_effectDictionary;	//エフェクトをファイルパスのハッシュ値をキーに持つ。
};