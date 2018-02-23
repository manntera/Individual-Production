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


private:
	Primitive		m_primitive;	//プリミティブ
	LPD3DXEFFECT	m_pEffect;		//エフェクト
	bool			m_isActive;	//アクティブか？
};