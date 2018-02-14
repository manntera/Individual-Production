#pragma once
class Camera
{
public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//アスペクト比を設定
	void SetAspect(float _aspect);

	//アスペクト比を取得
	float GetAspect() const;

	//ファーを設定
	void SetFar(float _far);

	//ファーを取得
	float GetFar() const;

	//ニアを設定
	void SetNear(float _near);

	//ニアを取得
	float GetNear() const;

	//視点を設定
	void SetTarget(const D3DXVECTOR3& target);

	//視点を取得
	const D3DXVECTOR3& GetTarget() const;

	//座標を設定
	void SetPosition(const D3DXVECTOR3& position);

	//座標を取得
	const D3DXVECTOR3& GetPosition() const;

	//カメラの上方向を設定
	void SetUp(const D3DXVECTOR3& up);

	//カメラの上方向を取得
	const D3DXVECTOR3& GetUp() const;

	//ビュー行列の設定。
	void SetViewMatrix(const D3DXMATRIX& view);

	//ビュー行列の取得
	const D3DXMATRIX& GetViewMatrix() const;

	//プロジェクション行列の設定。
	void SetProjectionMatrix(const D3DXMATRIX& projection);

	//プロジェクション行列の取得。
	const D3DXMATRIX& GetProjectionMatrix() const;

	//初期化
	void Init();

	//更新処理
	void Update();

private:
	D3DXMATRIX			m_viewMatrix;			//ビュー行列。カメラ行列とも言う。
	D3DXMATRIX			m_projectionMatrix;		//プロジェクション行列。ビュー空間から射影空間に変換する。
	D3DXVECTOR3			m_position;				//カメラの視点。
	D3DXVECTOR3			m_target;				//カメラの注視点
	D3DXVECTOR3			m_up;					//カメラの上方向
	float				m_Far;					//遠平面
	float				m_Near;					//近平面
	float				m_Aspect;				//アスペクト比
};