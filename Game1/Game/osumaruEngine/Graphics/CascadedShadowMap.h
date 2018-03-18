#pragma once
class SkinModel;
class Camera;

class CascadedShadowMap
{
public:
	//コンストラクタ
	CascadedShadowMap();

	//デストラクタ
	~CascadedShadowMap();

	void Init(int width, int height, float lightHeight);

	void Update();

	void Draw();

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
		m_isActive = true;
	}

	const D3DXMATRIX& GetViewMatrix(int index) const
	{
		return m_viewMatrix[index];
	}

	const D3DXMATRIX& GetProjectionMatrix(int index) const
	{
		return m_projMatrix[index];
	}

	void Entry(SkinModel* model)
	{
		m_models.push_back(model);
	}

	void SetUp(D3DXVECTOR3 up)
	{
		m_up = up;
	}

	void SetTarget(D3DXVECTOR3 target)
	{
		m_target = target;
	}
private:
	static const int		SHADOWMAP_NUM = 3;
	RenderTarget			m_renderTarget[SHADOWMAP_NUM];		//シャドウマップ
	D3DXVECTOR3				m_target;			//ライトの方向
	D3DXVECTOR3				m_up;				//ライトの上向き
	D3DXMATRIX				m_viewMatrix[SHADOWMAP_NUM];		//ライトのビュー行列
	D3DXMATRIX				m_projMatrix[SHADOWMAP_NUM];		//ライトのプロジェクション行列
	int						m_width;			//ウィンドウの幅
	int						m_height;			//ウィンドウの高さ
	std::list<SkinModel*>	m_models;			//シャドウマップに描画するモデル
	Camera*					m_pCamera;
	bool					m_isActive;
	float m_lightHeight;
};