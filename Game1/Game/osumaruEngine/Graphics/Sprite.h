#pragma once
#include "Primitive.h"
#include "Texture.h"
class Texture;

//スプライトクラス

class Sprite : Uncopyable
{
public:
	//コンストラクタ
	Sprite();

	//デストラクタ
	~Sprite();

	//初期化
	void Init(char *filePath);

	//描画
	void Draw();

	//座標をセット
	void SetPosition(D3DXVECTOR2 position)
	{
		m_position = position;
	}

	//座標を取得
	D3DXVECTOR2 GetPosition()
	{
		return m_position;
	}

	//サイズを設定
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//サイズを取得
	D3DXVECTOR2 GetSize()
	{
		return m_size;
	}

	//メモリを解放
	void Release();

private:
	float			m_alpha;
	Texture			m_texture;			//テクスチャ
	D3DXVECTOR2		m_position;			//スプライトのウィンドウ上での座標
	D3DXVECTOR2		m_centerPosition;	//スプライトの基点を表す座標
	D3DXVECTOR2		m_size;				//スプライトのサイズ
	LPD3DXEFFECT	m_pEffect;			//スプライト用のエフェクト
	Primitive		m_primitive;		//プリミティブ
};