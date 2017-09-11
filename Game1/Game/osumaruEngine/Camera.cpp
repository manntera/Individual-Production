#include "engineStdafx.h"
#include "Camera.h"
#include "Engine.h"

Camera::Camera()
{
	m_Near = 0.1f;
	m_Far = 1000.0f;
	m_Aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
}

Camera::~Camera()
{
}

void Camera::SetAspect(float _aspect)
{
	m_Aspect = _aspect;
}

float Camera::GetAspect()
{
	return m_Aspect;
}

void  Camera::SetFar(float _far)
{
	m_Far = _far;
}

float Camera::GetFar()
{
	return m_Far;
}

void Camera::SetNear(float _near)
{
	m_Near = _near;
}

float Camera::GetNear()
{
	return m_Near;
}

void Camera::SetTarget(D3DXVECTOR3 target)
{
	m_target = target;
}

D3DXVECTOR3 Camera::GetTarget()
{
	return m_target;
}

void Camera::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return m_position;
}

void Camera::SetUp(D3DXVECTOR3 up)
{
	m_up = up;
}

D3DXVECTOR3 Camera::GetUp()
{
	return m_up;
}

void Camera::SetViewMatrix(D3DXMATRIX view)
{
	m_viewMatrix = view;
}

D3DXMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}

void Camera::SetProjectionMatrix(D3DXMATRIX projection)
{
	m_projectionMatrix = projection;
}

D3DXMATRIX Camera::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

void Camera::Update()
{
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_target, &m_up);
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, m_Aspect, m_Near, m_Far);
}

void Camera::Init()
{
	m_position = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	m_target = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Update();
}