#pragma once
#include "Camera.h"
//バネカメラ

class SpringCamera
{
public:
	//コンストラクタ
	SpringCamera();

	//デストラクタ
	~SpringCamera();

	/*
	初期化
	*/
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);

	
	//目標となる注視点を設定。
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}

	//注視点を設定
	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetTarget(target);
	}

	
	//目標となる視点を設定
	void SetTarPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
	}

	//視点を設定
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_camera.SetPosition(position);
	}

	//遠平面を取得
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}

	//注視点を取得
	const D3DXVECTOR3& GetTarget() const
	{
		return m_camera.GetTarget();
	}

	//視点を取得
	const D3DXVECTOR3& GetPosition() const
	{
		return m_camera.GetPosition();
	}

	//更新関数
	void Update();

	//カメラを取得
	const Camera* GetCamera() const
	{
		return &m_camera;
	}

	/*
	バネの減衰率を設定
	dampingRate		減衰率、この値が大きいほどカメラが遅れてついてくる
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}

	//目標となる注視点を取得
	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}

	//目標となる視点を取得
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}

	//バネカメラ用のパラメータをクリア
	void ClearSpringParame()
	{
		m_target = {0.0f, 0.0f, 0.0f};
		m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	/*
	バネカメラの更新
	バネカメラのみ更新したいときに使う
	*/
	void UpdateSpringCamera();

	/*
	カメラの更新
	カメラのみ更新したいときに使う
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}
private:

	D3DXVECTOR3 CalcSpringVector(const D3DXVECTOR3& positionNow, const D3DXVECTOR3& positionTarget, D3DXVECTOR3& moveSpeed, float maxMoveSpeed, float dampingRate);

	float CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed);
private:
	Camera		m_camera;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_targetMoveSpeed;
	D3DXVECTOR3 m_positionMoveSpeed;
	float		m_maxMoveSpeed;
	float		m_targetDampingRate;
	float		m_dampingRate;
	float		m_dampingRateVel;
	const float m_dampingK;
};