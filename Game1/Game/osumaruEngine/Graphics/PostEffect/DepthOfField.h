#pragma once
//被写界深度のクラス

class DepthOfField : Uncopyable
{
public:
	//コンストラクタ
	DepthOfField();

	//デストラクタ
	~DepthOfField();

	/*
	初期化関数
	isActive アクティブか？
	*/
	void Init(bool isActive);

	//描画関数
	void Draw();

	//深度値書き込み用のレンダリングターゲットを取得
	const RenderTarget& GetDepthRendertarget() const
	{
		return m_depthTarget;
	}

private:
	const static int	BLUR_RANGE = 8;			//ブラーをかけるピクセルの範囲
	bool				m_isActive;				//アクティブか？
	RenderTarget		m_depthTarget;			//深度書き込み用のレンダリングターゲット
	RenderTarget		m_blur[2];				//ブラーをかけるぼかし用のレンダリングターゲット
	float				m_weight[BLUR_RANGE];	//ガウスブラーのウェイト
	LPD3DXEFFECT		m_pEffect;				//エフェクト
	Primitive			m_primitive;			//プリミティブ
};
