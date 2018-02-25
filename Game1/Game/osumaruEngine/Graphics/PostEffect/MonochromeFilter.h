#pragma once
//モノクロフィルター

class MonochromeFilter
{
public:
	//コンストラクタ
	MonochromeFilter();

	//デストラクタ
	~MonochromeFilter();

	/*
	初期化関数
	isActive	アクティブか？
	*/
	void Init(bool isActive);

	//描画関数
	void Draw();

	//アクティブにするかを設定
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

	//アルファ値を設定
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

private:
	Primitive		m_primitive;	//プリミティブ
	LPD3DXEFFECT	m_pEffect;		//エフェクト
	bool			m_isActive;		//アクティブか？
	float			m_alpha;		//アルファ値
};