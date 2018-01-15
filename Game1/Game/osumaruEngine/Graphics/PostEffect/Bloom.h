#pragma once
//ブルームクラス

class Bloom : Uncopyable
{
public:
	//コンストラクタ
	Bloom();

	//デストラクタ
	~Bloom();

	/*
	初期化関数
	isActive	アクティブか？
	*/
	void Init(bool isActive);

	//描画関数
	void Draw();

	//ガウスブラーのウェイトを設定
	void SetWeight(float rate);
private:
	const static int BLUR_RANGE = 8;							//ブラーをかけるピクセルの範囲
	const static int DOWN_SAMPLING_NUM = 5;						//ダウンサンプリング
	RenderTarget m_downSamplingTarget[DOWN_SAMPLING_NUM][2];	//ダウンサンプリング用のレンダリングターゲット
	RenderTarget m_luminanceTarget;								//輝度抽出用のレンダリングターゲット
	RenderTarget m_combineTarget;								//最終的に合成するようのレンダリングターゲット
	LPD3DXEFFECT m_pEffect;										//エフェクト
	float		 m_weight[BLUR_RANGE];							//ガウスブラーのウェイト
	Primitive	 m_primitive;									//プリミティブ
	bool		 m_isActive;									//アクティブか？
};