#pragma once
#include "RenderTarget.h"
//シャドウマップクラス

class SkinModel;

class ShadowMap : Uncopyable
{
public:
	//コンストラクタ
	ShadowMap();

	//デストラクタ
	~ShadowMap();
	
	/*
	シャドウマップを作る関数
	width		ウィンドウの幅
	height		ウィンドウの高さ
	*/
	void Create(int width, int height);

	/*
	シャドウマップにエントリー(毎フレームリセットするのでその都度エントリーする必要あり
	model		シャドウマップにエントリーするモデル
	*/
	void Entry(SkinModel* model);

	//更新関数
	void Update();

	/*
	シャドウマップに描画
	*/
	void Draw();

	//シャドウマップのテクスチャを取得
	const LPDIRECT3DTEXTURE9 GetShadowMapTexture() const;

	//ライトの注視点を設定
	void SetLightCameraTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}

	//座標を設定
	void SetLightCameraUp(D3DXVECTOR3 up)
	{
		m_up = up;
	}
	
	//座標を設定
	void SetLightCameraPosition(D3DXVECTOR3 position)
	{
		m_position = position;
	}

	//ライトカメラのビュー行列を取得
	const D3DXMATRIX& GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	//ライトカメラのプロジェクション行列を取得
	const D3DXMATRIX& GetProjectionMatrix() const
	{
		return m_projMatrix;
	}
private:
	RenderTarget			m_renderTarget;		//シャドウマップ
	D3DXVECTOR3				m_position;			//ライトの座標
	D3DXVECTOR3				m_target;			//ライトの注視点
	D3DXVECTOR3				m_up;				//ライトの上向き
	D3DXMATRIX				m_viewMatrix;		//ライトのビュー行列
	D3DXMATRIX				m_projMatrix;		//ライトのプロジェクション行列
	int						m_width;			//ウィンドウの幅
	int						m_height;			//ウィンドウの高さ
	std::list<SkinModel*>	m_models;				//シャドウマップに描画するモデル
};