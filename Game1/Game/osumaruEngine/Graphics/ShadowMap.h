#pragma once
//シャドウマップクラス

class SkinModel;

class ShadowMap
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
	LPDIRECT3DTEXTURE9 GetShadowMapTexture();

	void SetTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}

	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
	}

	D3DXMATRIX GetViewMatrix()
	{
		return m_viewMatrix;
	}

	D3DXMATRIX GetProjMatrix()
	{
		return m_projMatrix;
	}
	
	void Release();


private:
	LPDIRECT3DTEXTURE9		m_pShadowMap;
	D3DXVECTOR3				m_position;
	D3DXVECTOR3				m_target;
	D3DXVECTOR3				m_up;
	D3DXMATRIX				m_viewMatrix;
	D3DXMATRIX				m_projMatrix;
	int						m_width;
	int						m_height;
	std::vector<SkinModel*> m_models;
};