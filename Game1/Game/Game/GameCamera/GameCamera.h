#pragma once
//ゲームカメラクラス

class GameCamera : public GameObject
{
public:
	//コンストラクタ
	GameCamera();
	
	//デストラクタ
	~GameCamera();

	//初期化関数
	void Init();

	//更新関数
	void Update()override;

	//カメラの取得
	Camera& GetCamera()
	{
		return camera;
	}

private:
	D3DXQUATERNION	rotation;		//カメラの回転
	Camera			camera;			//カメラ

};