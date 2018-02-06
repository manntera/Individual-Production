#include "engineStdafx.h"
#include "ShadowMap.h"
#include "../Engine.h"
#include "SkinModel\SkinModel.h"

ShadowMap::ShadowMap() :
	m_renderTarget(),
	m_position(0.0f, 0.0f, 0.0f),
	m_target(0.0f, 0.0f, 0.0f),
	m_up(0.0f, 1.0f, 0.0f),
	m_viewMatrix{},
	m_projMatrix{},
	m_width(0),
	m_height(0),
	m_models()
{
}

ShadowMap::~ShadowMap()
{
}

void ShadowMap::Create(int width, int height)
{
	m_width = width;
	m_height = height;
	//シャドウマップを作成
	m_renderTarget.Create(m_width, m_height, D3DFMT_A8R8G8B8, D3DFMT_D16);
}

void ShadowMap::Update()
{
	D3DXVECTOR3 direction = m_target - m_position;
	D3DXVec3Normalize(&direction, &direction);
	if (0.999f < fabs(D3DXVec3Dot(&direction, &D3DXVECTOR3(0.0f, 1.0f, 0.0f))) )
	{
		m_up = { 1.0f, 0.0f, 0.0f };
	}
	else
	{
		m_up = { 0.0f, 1.0f, 0.0f };
	}
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_target, &m_up);
	//D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DXToRadian(60.0f), 1.0f, 1.0f, 100.0f);
	D3DXMatrixOrthoLH(&m_projMatrix, 100.0f, 100.0f, 3.0f, 300.0f);
}

void ShadowMap::Entry(SkinModel* model)
{
	m_models.push_back(model);
}

void ShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTargetBackup;	//レンダーターゲットを戻すためのバックアップ
	LPDIRECT3DSURFACE9 depthBufferBackup;	//深度ステンシルバッファを戻すためのバックアップ

	GetEngine().GetDevice()->GetRenderTarget(0, &renderTargetBackup);
	GetEngine().GetDevice()->GetDepthStencilSurface(&depthBufferBackup);
	GetEngine().GetDevice()->SetRenderTarget(0, m_renderTarget.GetRenderTarget());
	GetEngine().GetDevice()->SetDepthStencilSurface(m_renderTarget.GetDepthStencilBuffer());
	//描画
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
		model->Draw(&m_viewMatrix, &m_projMatrix);
		model->SetShaderTechnique(shaderTechniqueBackup);
		if (model->IsShadowCompesation())
		{
			model->UpdateWorldMatrix(trans, rot, scale);
		}
	}
	GetEngine().GetDevice()->EndScene();
	GetEngine().GetDevice()->SetRenderTarget(0, renderTargetBackup);
	GetEngine().GetDevice()->SetDepthStencilSurface(depthBufferBackup);
	renderTargetBackup->Release();
	depthBufferBackup->Release();
	m_models.clear();
}

const LPDIRECT3DTEXTURE9 ShadowMap::GetShadowMapTexture() const
{
	return m_renderTarget.GetTexture();
}