#pragma once

class RenderTarget
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
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_pTexture;
	}

	//レンダーターゲットを取得
	LPDIRECT3DSURFACE9 GetRenderTarget()
	{
		return m_pRenderTarget;
	}

	//深度ステンシルバッファを取得
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}

	//解放処理
	void Release();


private:
	LPDIRECT3DTEXTURE9		m_pTexture;			//テクスチャ
	LPDIRECT3DSURFACE9		m_pDepthBuffer;		//深度ステンシルバッファ
	LPDIRECT3DSURFACE9		m_pRenderTarget;	//レンダリングターゲット
};