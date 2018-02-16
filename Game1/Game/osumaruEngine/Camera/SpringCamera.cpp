#include "engineStdafx.h"
#include "SpringCamera.h"

SpringCamera::SpringCamera() :
	m_camera(),
	m_target(0.0f, 0.0f, 0.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_targetMoveSpeed(0.0f, 0.0f, 0.0f),
	m_positionMoveSpeed(0.0f, 0.0f, 0.0f),
	m_maxMoveSpeed(0.0f),
	m_targetDampingRate(0.0f),
	m_dampingRate(1.0f),
	m_dampingRateVel(0.0f),
	m_dampingK(30.0f)
{

}

SpringCamera::~SpringCamera()
{

}

void SpringCamera::Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed)
{
	m_camera.SetTarget(target);

	m_camera.SetPosition(position);
	m_target = target;
	m_position = position;
	m_targetMoveSpeed = { 0.0f, 0.0f, 0.0f };
	m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	m_maxMoveSpeed = maxMoveSpeed;
}

float SpringCamera::CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed)
{
	float deltaTime = GetGameTime().GetDeltaFrameTime();
	float dampingRate = 0.2f;
	float distance = positionTarget - positionNow;
	if (fabsf(distance) < FLT_EPSILON)
	{
		moveSpeed = 0.0f;
		return positionTarget;
	}
	float originalDir = distance;
	originalDir /= fabsf(distance);
	float springAccel = distance;

	float t = m_dampingK / (2.0f * dampingRate);
	float springK = t * t;
	springAccel *= springK;
	//加速度を決定。
	float vt = moveSpeed;
	vt *= m_dampingK;
	springAccel -= vt;
	springAccel *= deltaTime;
	moveSpeed += springAccel;

	float newPos = positionNow;
	float addPos = moveSpeed;
	addPos *= deltaTime;
	newPos += addPos;
	vt = positionTarget - newPos;
	if (fabsf(vt) < FLT_EPSILON)
	{
		//目標座標まで移動完了した
		newPos = positionTarget;
		moveSpeed = 0.0f;
	}
	else
	{
		if (vt * originalDir < 0.0f)
		{
			//目標座標を超えた。
			newPos = positionTarget;
			moveSpeed = 0.0f;
		}
	}
	return newPos;
}

D3DXVECTOR3 SpringCamera::CalcSpringVector(const D3DXVECTOR3& positionNow, const D3DXVECTOR3& positionTarget, D3DXVECTOR3& moveSpeed, float maxMoveSpeed, float dampingRate)
{
	float deltaTime = GetGameTime().GetDeltaFrameTime();
	//現在の位置と目標の位置との差分を求める。
	D3DXVECTOR3 distance;
	distance = positionTarget - positionNow;
	D3DXVECTOR3 originalDir = distance;
	D3DXVec3Normalize(&originalDir, &originalDir);
	D3DXVECTOR3 springAccel;
	springAccel = distance;
	
	float t = m_dampingK / (2.0f * dampingRate);
	float springK = t * t;
	springAccel *= springK;
	//加速度を決定。
	D3DXVECTOR3 vt = moveSpeed;
	vt *= m_dampingK;
	springAccel -= vt;

	springAccel *= deltaTime;
	moveSpeed += springAccel;
	if (D3DXVec3LengthSq(&moveSpeed) > maxMoveSpeed * maxMoveSpeed)
	{
		//最高速度より早くなってしまった
		D3DXVec3Normalize(&moveSpeed, &moveSpeed);
		moveSpeed *= maxMoveSpeed;
	}
	D3DXVECTOR3 newPos = positionNow;
	D3DXVECTOR3 addPos = moveSpeed;
	addPos *= deltaTime;
	newPos += addPos;
	vt = positionTarget - newPos;
	D3DXVec3Normalize(&vt, &vt);
	if (D3DXVec3Dot(&vt, &originalDir) < 0.0f)
	{
		//目標座標を超えた
		newPos = positionTarget;
		moveSpeed = { 0.0f, 0.0f, 0.0f };
	}
	return newPos;

}

void SpringCamera::UpdateSpringCamera()
{
	m_dampingRate = CalcSpringScalar(m_dampingRate, m_targetDampingRate, m_dampingRateVel);
	D3DXVECTOR3 target = CalcSpringVector(m_camera.GetTarget(), m_target, m_targetMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	D3DXVECTOR3 position = CalcSpringVector(m_camera.GetPosition(), m_position, m_positionMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	m_camera.SetTarget(target);
	m_camera.SetPosition(position);
}

void SpringCamera::Update()
{
	UpdateSpringCamera();
	UpdateCamera();
}