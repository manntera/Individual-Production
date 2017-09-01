#include "engineStdafx.h"
#include "Camera.h"
#include "Engine.h"

Camera::Camera()
{
	Near = 0.1f;
	Far = 100.0f;
	Aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
}

Camera::~Camera()
{
}

void Camera::SetAspect(float _aspect)
{
	Aspect = _aspect;
}

float Camera::GetAspect()
{
	return Aspect;
}

void  Camera::SetFar(float _far)
{
	Far = _far;
}

float Camera::GetFar()
{
	return Far;
}

void Camera::SetNear(float _near)
{
	Near = _near;
}

float Camera::GetNear()
{
	return Near;
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
	viewMatrix = view;
}

D3DXMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::SetProjectionMatrix(D3DXMATRIX projection)
{
	projectionMatrix = projection;
}

D3DXMATRIX Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &m_position, &m_target, &m_up);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, Aspect, Near, Far);
}

void Camera::Init()
{
	m_position = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	m_target = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Update();
}