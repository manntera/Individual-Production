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
	m_dampingRate(0.0f),
	m_dampingRateVel(0.0f),
	m_dampingK(35.0f)
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
	return 0.0f;
}

D3DXVECTOR3 SpringCamera::CalcSpringVector(const D3DXVECTOR3& positionNow, const D3DXVECTOR3& positionTarget, D3DXVECTOR3& moveSpeed, float maxMoveSpeed, float dampingRate)
{
	return{ 0.0f, 0.0f, 0.0f };
}

void SpringCamera::UpdateSpringCamera()
{
	m_dampingRate = CalcSpringScalar(m_targetDampingRate, m_dampingRate, m_dampingRateVel);
	D3DXVECTOR3 target = CalcSpringVector(m_camera.GetTarget(), m_target, m_targetMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	D3DXVECTOR3 position = CalcSpringVector(m_camera.GetPosition(), m_position, m_positionMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	
}

void SpringCamera::Update()
{
	UpdateSpringCamera();
	UpdateCamera();
}