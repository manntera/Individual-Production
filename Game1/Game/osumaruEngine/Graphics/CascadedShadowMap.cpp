#include "engineStdafx.h"
#include "CascadedShadowMap.h"
#include "../Engine.h"
#include "SkinModel\SkinModel.h"
#include "../Camera/Camera.h"


CascadedShadowMap::CascadedShadowMap()
{

}

CascadedShadowMap::~CascadedShadowMap()
{

}

void CascadedShadowMap::Init(int width, int height, float lightHeight)
{
	for (int i = 0;i < SHADOWMAP_NUM;i++)
	{

		m_renderTarget[i].Create(width >> i, height >> i, D3DFMT_R32F, D3DFMT_D16);
		D3DXMatrixIdentity(&m_viewMatrix[i]);
		D3DXMatrixIdentity(&m_projMatrix[i]);
	}
	m_isActive = false;
	m_height = lightHeight;
	
}

void CascadedShadowMap::Update()
{
	if (!m_isActive)
	{
		return;
	}
	D3DXVECTOR3 lightCameraForward = m_target;
	D3DXVECTOR3 lightCameraUp = m_up;
	D3DXVec3Normalize(&lightCameraForward, &lightCameraForward);
	D3DXVec3Normalize(&lightCameraUp, &lightCameraUp);
	D3DXVECTOR3 lightCameraRight;
	D3DXVec3Cross(&lightCameraRight, &lightCameraUp, &lightCameraForward);
	D3DXVec3Normalize(&lightCameraRight, &lightCameraRight);
	D3DXMATRIX lightCameraRot;
	lightCameraRot.m[0][0] = lightCameraRight.x;
	lightCameraRot.m[0][1] = lightCameraRight.y;
	lightCameraRot.m[0][2] = lightCameraRight.z;
	lightCameraRot.m[0][3] = 0.0f;
	lightCameraRot.m[1][0] = lightCameraUp.x;
	lightCameraRot.m[1][1] = lightCameraUp.y;
	lightCameraRot.m[1][2] = lightCameraUp.z;
	lightCameraRot.m[1][3] = 0.0f;
	lightCameraRot.m[2][0] = lightCameraForward.x;
	lightCameraRot.m[2][1] = lightCameraForward.y;
	lightCameraRot.m[2][2] = lightCameraForward.z;
	lightCameraRot.m[2][3] = 0.0f;
	float _near = 0.0f;
	float _far;
	float ZLength = 300.0f;
	float shadowAreaTable[SHADOWMAP_NUM] =
	{
		ZLength * 0.3f,
		ZLength * 0.6f,
		ZLength * 1.2f
	};
	D3DXVECTOR3 cameraForward = m_pCamera->GetTarget() - m_pCamera->GetPosition();
	cameraForward.y = 0.0f;
	D3DXVec3Normalize(&cameraForward, &cameraForward);
	D3DXVECTOR3 cameraUp = m_pCamera->GetUp();
	D3DXVECTOR3 cameraRight;
	D3DXVec3Cross(&cameraRight, &cameraUp, &cameraForward);
	D3DXVec3Cross(&cameraUp, &cameraForward, &cameraRight);
	D3DXVec3Normalize(&cameraUp, &cameraUp);
	D3DXVec3Normalize(&cameraRight, &cameraRight);
	float halfAngle = m_pCamera->GetAngle() * 0.5f;
	float t = tan(halfAngle);
	float _aspect = m_pCamera->GetAspect();
	for (int i = 0;i < SHADOWMAP_NUM;i++)
	{
		_far = shadowAreaTable[i] + _near;
		D3DXVECTOR3 cameraCenter = m_pCamera->GetPosition() + cameraForward * _near;
		D3DXVECTOR3 lightPos = cameraCenter;
		D3DXVECTOR3 aabbVertex[8];
		D3DXVECTOR3 cameraUpNear = cameraUp * t * _near;
		D3DXVECTOR3 cameraUpFar = cameraUp * t * _far;
		t *= _aspect;
		D3DXVECTOR3 cameraRightNear = cameraRight * t * _near;
		D3DXVECTOR3 cameraRightFar = cameraRight * t * _far;
		aabbVertex[0] = cameraCenter + cameraUpNear + cameraRightNear;
		aabbVertex[1] = aabbVertex[0] - cameraUpNear * 2.0f;
		aabbVertex[2] = aabbVertex[0] - cameraRightNear * 2.0f;
		aabbVertex[3] = aabbVertex[1] - cameraRightNear * 2.0f;
		cameraCenter = m_pCamera->GetPosition() + cameraForward * _far;
		lightPos += cameraCenter;
		lightPos *= 0.5f;
		aabbVertex[4] = cameraCenter + cameraUpFar + cameraRightFar;
		aabbVertex[5] = aabbVertex[4] - cameraUpFar * 2.0f;
		aabbVertex[6] = aabbVertex[4] - cameraRightFar * 2.0f;
		aabbVertex[7] = aabbVertex[5] - cameraRightFar * 2.0f;
		D3DXMATRIX lightView = lightCameraRot;
		lightPos.y += m_lightHeight;
		lightView.m[3][0] = lightPos.x;
		lightView.m[3][1] = lightPos.y;
		lightView.m[3][2] = lightPos.z;
		lightView.m[3][3] = 1.0f;
		D3DXMatrixInverse(&lightView, NULL, &lightView);
		D3DXVECTOR3 aabbMin = { FLT_MAX, FLT_MAX, FLT_MAX };
		D3DXVECTOR3 aabbMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
		for (int i = 0;i < 8;i++)
		{
			D3DXVec3TransformCoord(&aabbVertex[i], &aabbVertex[i], &lightView);
			D3DXVec3Maximize(&aabbMax, &aabbVertex[i], &aabbMax);
			D3DXVec3Minimize(&aabbMin, &aabbVertex[i], &aabbMin);
		}
		D3DXVECTOR3 lightTarget = lightPos + lightCameraForward;
		float w = aabbMax.x - aabbMin.x;
		float h = aabbMax.y - aabbMin.y;
		D3DXMatrixLookAtLH(&m_viewMatrix[i], &lightPos, &lightTarget, &lightCameraUp);
		D3DXMatrixOrthoLH(&m_projMatrix[i], w, h, 10.0f, 1000.0f);
		_near = _far;
	}

}

void CascadedShadowMap::Draw()
{

	LPDIRECT3DSURFACE9 renderTargetBackup;	//�����_�[�^�[�Q�b�g��߂����߂̃o�b�N�A�b�v
	LPDIRECT3DSURFACE9 depthBufferBackup;	//�[�x�X�e���V���o�b�t�@��߂����߂̃o�b�N�A�b�v
	GetEngine().GetDevice()->GetRenderTarget(0, &renderTargetBackup);
	GetEngine().GetDevice()->GetDepthStencilSurface(&depthBufferBackup);
	for (int i = 0;i < SHADOWMAP_NUM;i++)
	{
		GetEngine().GetDevice()->SetRenderTarget(0, m_renderTarget[i].GetRenderTarget());
		GetEngine().GetDevice()->SetDepthStencilSurface(m_renderTarget[i].GetDepthStencilBuffer());
		//�`��
		GetEngine().GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		GetEngine().GetDevice()->BeginScene();
		for (SkinModel* model : m_models)
		{
			EnSkinModelShaderTechnique shaderTechniqueBackup = model->GetCurrentShaderTechnique();
			D3DXVECTOR3 trans;
			D3DXQUATERNION rot;
			D3DXVECTOR3 scale;
			if (model->IsShadowCompesation())
			{
				trans = model->GetPosition();
				rot = model->GetRotation();
				scale = model->GetScale();
				model->UpdateWorldMatrix(trans, rot, scale * 0.95f);
			}
			model->SetShaderTechnique(enShaderTechniqueShadow);
			model->Draw(&m_viewMatrix[i], &m_projMatrix[i]);
			model->SetShaderTechnique(shaderTechniqueBackup);
			if (model->IsShadowCompesation())
			{
				model->UpdateWorldMatrix(trans, rot, scale);
			}
		}
		GetEngine().GetDevice()->EndScene();

	}
	m_models.clear();
	GetEngine().GetDevice()->SetRenderTarget(0, renderTargetBackup);
	GetEngine().GetDevice()->SetDepthStencilSurface(depthBufferBackup);
	renderTargetBackup->Release();
	depthBufferBackup->Release();
}