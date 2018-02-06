#pragma once

class RenderTarget : Uncopyable
{
public:
	//コンストラクタ
	RenderTarget();

	//デストラクタ
	~RenderTarget();
	
	/*
	レンダーターゲットを作成
	width		テクスチャの幅
	height		テクスチャの高さ
	format		テクスチャのフォーマット
	depthFormat	デプスステンシルバッファのフォーマット
	*/
	void Create(int width, int height, D3DFORMAT format, D3DFORMAT depthFormat);

	//テクスチャを取得
	const LPDIRECT3DTEXTURE9 GetTexture() const
	{
		return m_pTexture;
	}

	//レンダーターゲットを取得
	const LPDIRECT3DSURFACE9 GetRenderTarget() const
	{
		return m_pRenderTarget;
	}

	//深度ステンシルバッファを取得
	const LPDIRECT3DSURFACE9 GetDepthStencilBuffer() const
	{
		return m_pDepthBuffer;
	}

	//テクスチャの幅を取得
	int GetWidth() const
	{
		return m_width;
	}

	//テクスチャの高さを取得。
	int GetHeight() const
	{
		return m_height;
	}

	//解放処理
	void Release();


private:
	LPDIRECT3DTEXTURE9		m_pTexture;			//テクスチャ
	LPDIRECT3DSURFACE9		m_pDepthBuffer;		//深度ステンシルバッファ
	LPDIRECT3DSURFACE9		m_pRenderTarget;	//レンダリングターゲット
	int						m_width;			//テクスチャの幅
	int						m_height;			//テクスチャの高さ
};