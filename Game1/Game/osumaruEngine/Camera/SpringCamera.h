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

	
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}

	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetTarget(target);
	}

	void SetTarPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
	}

	void SetPosition(const D3DXVECTOR3& position)
	{
		m_camera.SetPosition(position);
	}

	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}

	const D3DXVECTOR3& GetTarget() const
	{
		return m_camera.GetTarget();
	}

	const D3DXVECTOR3& GetPosition() const
	{
		return m_camera.GetPosition();
	}

	void Update();

	const Camera* GetCamera() const
	{
		return &m_camera;
	}

	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}

	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}

	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}

	void ClearSpringParame()
	{
		m_target = {0.0f, 0.0f, 0.0f};
		m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	void UpdateSpringCamera();

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