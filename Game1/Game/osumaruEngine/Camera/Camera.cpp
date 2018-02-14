#include "engineStdafx.h"
#include "Camera.h"
#include "Engine.h"

Camera::Camera() :
	m_viewMatrix{},
	m_projectionMatrix{},
	m_position(0.0f, 0.0f, 0.0f),
	m_target(0.0f, 0.0f, 0.0f),
	m_up(0.0f, 1.0f, 0.0f),
	m_Far(1000.0),
	m_Near(0.1f),
	m_Aspect((float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT)
{
	D3DXMatrixIdentity(&m_viewMatrix);
	D3DXMatrixIdentity(&m_projectionMatrix);
}

Camera::~Camera()
{
}

void Camera::SetAspect(float _aspect)
{
	m_Aspect = _aspect;
}

float Camera::GetAspect() const
{
	return m_Aspect;
}

void  Camera::SetFar(float _far)
{
	m_Far = _far;
}

float Camera::GetFar() const
{
	return m_Far;
}

void Camera::SetNear(float _near)
{
	m_Near = _near;
}

float Camera::GetNear() const
{
	return m_Near;
}

void Camera::SetTarget(const D3DXVECTOR3& target)
{
	m_target = target;
}

const D3DXVECTOR3& Camera::GetTarget() const
{
	return m_target;
}

void Camera::SetPosition(const D3DXVECTOR3& position)
{
	m_position = position;
}

const D3DXVECTOR3& Camera::GetPosition() const
{
	return m_position;
}

void Camera::SetUp(const D3DXVECTOR3& up)
{
	m_up = up;
}

const D3DXVECTOR3& Camera::GetUp() const
{
	return m_up;
}

void Camera::SetViewMatrix(const D3DXMATRIX& view)
{
	m_viewMatrix = view;
}

const D3DXMATRIX& Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

void Camera::SetProjectionMatrix(const D3DXMATRIX& projection)
{
	m_projectionMatrix = projection;
}

const D3DXMATRIX& Camera::GetProjectionMatrix() const
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