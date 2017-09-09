#pragma once
//アニメーションを管理するクラス

class Animation
{
public:
	Animation()
	{
		pAnimController = nullptr;
		numAnimSet = 0;
		isBlending = false;
		isInterpolate = false;
		numMaxTracks = 0;
		interpolateEndTime = 0.0f;
		interpolateTime = 0.0f;
	}
	~Animation()
	{

	}
	/*
	初期化
	anim		アニメーションコントローラー
	*/
	void Init(ID3DXAnimationController* anim);

	/*
	アニメーションの終了タイムを設定する。
	animationSetIndex			アニメーションインデックス。
	endTime						アニメーションの終了タイム。-1.0を設定するとアニメーションファイルに設定されている終了タイムになる
	*/
	void SetAnimationEndTime(int animationSetIndex, double endTime)
	{
		animationEndTime[animationSetIndex] = endTime;
	}
	/*
	アニメーションの再生
	animationIndex			再生したいアニメーションのインデックス
	*/
	void PlayAnimation(int animationSetIndex);

	/*
	アニメーションの再生。アニメーションの補間が行われます
	animationSetIndex				再生したいアニメーションのインデックス
	interpolateTime					補間時間。
	*/
	void PlayAnimation(int animationSetIndex, float interpolateTime);
#if 0
	/*
	アニメーションのブレンディング再生
	animationIndex			再生したいアニメーションのインデックス。
	*/
	void BlendAnimation(int animationSetIndex);
#endif
	/*
	アニメーションセットの取得
	*/
	int GetNumAnimationSet() const
	{
		return numAnimSet;
	}
	/*
	アニメーションの更新
	deltaTime		更新時間、単位は秒
	*/
	void Update(float deltaTime);

private:

	ID3DXAnimationController*				pAnimController;			//アニメーションコントローラー
	int										numAnimSet;					//アニメーションセットの数
	std::unique_ptr<ID3DXAnimationSet*[]>	animationSets;				//アニメーションの配列。
	std::unique_ptr<float[]>				blendRateTable;				//ブレンディングレートのテーブル。
	std::unique_ptr<double[]>				animationEndTime;			//アニメーションの終了タイム。デフォルトは-1.0が入っていて、-1.0が入っている場合はID3DXAnimationSetのアニメーション終了タイムが優先される。
																		//DirectX9のアニメーションセットに1秒以下のアニメーションを入れる方法が見つからない。一秒以下のアニメーションはこいつを適時設定。
	double									localAnimationTime;			//ローカルアニメーションタイム
	int										currentAnimationSetNo;		//現在再生中のアニメーショントラックの番号
	int										currentTrackNo;				//現在のトラックの番号
	int										numMaxTracks;				//アニメーショントラックの最大数
	bool									isBlending;					//アニメーションブレンディング中？
	bool									isInterpolate;				//補間中？
	float									interpolateEndTime;			//補間終了時間
	float									interpolateTime;			//補間時間
};	