#include "engineStdafx.h"
#include "ShadowMap.h"
#include "../Engine.h"
#include "SkinModel\SkinModel.h"

ShadowMap::ShadowMap()
{
	m_pShadowMap = nullptr;
	m_position = { 0.0f, 0.0f, 0.0f };
	m_target = { 0.0f, 0.0f, 0.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_width = 0;
	m_height = 0;
}

ShadowMap::~ShadowMap()
{
	Release();
}

void ShadowMap::Create(int width, int height)
{
	Release();
	m_width = width;
	m_height = height;
	GetEngine().GetDevice()->CreateTexture(
		m_width,
		m_height,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pShadowMap,
		NULL
	);
}

void ShadowMap::Update()
{
	float Near = 0.1f;
	float Far = 1000.0f;
	float Aspect = (float)m_width / (float)m_height;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, Aspect, Near, Far);
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_target, &m_up);
}

void ShadowMap::Entry(SkinModel* model)
{
	m_models.push_back(model);
}

void ShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTarget;
	LPDIRECT3DSURFACE9 shadowTarget;
	m_pShadowMap->GetSurfaceLevel(0, &shadowTarget);
	GetEngine().GetDevice()->GetRenderTarget(0, &renderTarget);

	GetEngine().GetDevice()->SetRenderTarget(0, shadowTarget);

	//描画
	// 画面をクリア。
	GetEngine().GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//pDevice->Present(NULL, NULL, NULL, NULL);
	//シーンの描画開始。
	GetEngine().GetDevice()->BeginScene();
	for (SkinModel* model : m_models)
	{
		model->Draw(&m_viewMatrix, &m_projMatrix, enPreRenderShadowMap);
	}
	// シーンの描画終了。
	GetEngine().GetDevice()->EndScene();

	GetEngine().GetDevice()->SetRenderTarget(0, renderTarget);
	m_models.clear();
}

LPDIRECT3DTEXTURE9 ShadowMap::GetShadowMapTexture()
{
	return m_pShadowMap;
}

void ShadowMap::Release()
{
	if (m_pShadowMap != nullptr)
	{
		m_pShadowMap->Release();
		m_pShadowMap = nullptr;
	}
}