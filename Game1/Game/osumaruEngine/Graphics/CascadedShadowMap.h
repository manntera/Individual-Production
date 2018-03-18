#pragma once
class SkinModel;
class Camera;
//カスケードシャドウマップ

class CascadedShadowMap
{
public:
	//コンストラクタ
	CascadedShadowMap();

	//デストラクタ
	~CascadedShadowMap();
	
	/*
	初期化
	width			テクスチャの幅
	height			テクスチャの縦幅
	lightHeight		ライトカメラの高さ
	*/
	void Init(int width, int height, float lightHeight);

	//更新
	void Update();

	//描画
	void Draw();

	/*
	シャドウマップのテクスチャを取得
	textureNum	テクスチャの配列のインデックス
	*/
	const LPDIRECT3DTEXTURE9 GetShadowMapTexture(int textureNum) const
	{
		return m_renderTarget[textureNum].GetTexture();
	}

	//ライトの注視点を設定
	void SetLightCameraTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}

	//座標を設定
	void SetLightCameraUp(const D3DXVECTOR3& up)
	{
		m_up = up;
	}

	//ゲームで使っているカメラの設定
	void SetGameCamera(Camera* camera)
	{
		m_pCamera = camera;
		if (m_pCamera != nullptr)
		{
			m_isActive = true;
		}
		else
		{
			m_isActive = false;
		}
	}

	/*
	ビュー行列を取得
	index	配列のインデックス
	*/
	const D3DXMATRIX& GetViewMatrix(int index) const
	{
		return m_viewMatrix[index];
	}
	/*
	プロジェクション行列を取得
	index	配列のインデックス
	*/
	const D3DXMATRIX& GetProjectionMatrix(int index) const
	{
		return m_projMatrix[index];
	}

	/*
	シャドウマップに描画するモデルを登録
	model	登録するモデル
	*/
	void Entry(SkinModel* model)
	{
		m_models.push_back(model);
	}

	//ライトカメラの上方向を決定
	void SetUp(D3DXVECTOR3 up)
	{
		m_up = up;
	}

	//ライトカメラの注視点を設定
	void SetTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}

	int GetShadowMapNum() const
	{
		return SHADOWMAP_NUM;
	}
private:
	static const int		SHADOWMAP_NUM = 3;					//シャドウマップの数
	RenderTarget			m_renderTarget[SHADOWMAP_NUM];		//シャドウマップ
	D3DXVECTOR3				m_target;							//ライトの方向
	D3DXVECTOR3				m_up;								//ライトの上向き
	D3DXMATRIX				m_viewMatrix[SHADOWMAP_NUM];		//ライトのビュー行列
	D3DXMATRIX				m_projMatrix[SHADOWMAP_NUM];		//ライトのプロジェクション行列
	int						m_width;							//ウィンドウの幅
	int						m_height;							//ウィンドウの高さ
	std::list<SkinModel*>	m_models;							//シャドウマップに描画するモデル
	Camera*					m_pCamera;							//メインのカメラ
	bool					m_isActive;							//アクティブか？
	float					m_lightHeight;						//ライトカメラの高さ
};