#include "engineStdafx.h"
#include "RenderTarget.h"
#include "../Engine.h"


RenderTarget::RenderTarget()
{
	m_pTexture = nullptr;
	m_pDepthBuffer = nullptr;
	m_pRenderTarget = nullptr;
}

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Create(int width, int height, D3DFORMAT format, D3DFORMAT depthFormat)
{
	//シャドウマップを作成
	GetEngine().GetDevice()->CreateTexture(
		width,
		height,
		1,
		D3DUSAGE_RENDERTARGET,
		format,
		D3DPOOL_DEFAULT,
		&m_pTexture,
		NULL
	);
	//深度ステンシルバッファを作成
	GetEngine().GetDevice()->CreateDepthStencilSurface(
		width,
		height,
		depthFormat,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pDepthBuffer,
		NULL
	);
	m_pTexture->GetSurfaceLevel(0, &m_pRenderTarget);
}

void RenderTarget::Release()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	if (m_pDepthBuffer != nullptr)
	{
		m_pDepthBuffer->Release();
		m_pDepthBuffer = nullptr;
	}
}