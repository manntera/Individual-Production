#pragma once

class SkinModelData;
class Animation;
//スキンモデルデータリソース

class SkinModelDataResource : Uncopyable
{
public:
	//コンストラクタ
	SkinModelDataResource();

	//デストラクタ
	~SkinModelDataResource();

	/*
	モデルデータをロード
	modelData	読み込んだモデルを入れるもの
	anim		アニメーション
	fileName	モデルのファイルパス
	*/
	void Load(SkinModelData* modelData, Animation* anim,  char* fileName);

private:
	std::map<int, SkinModelData*>	m_modelDatas;	//モデルデータのリスト
};