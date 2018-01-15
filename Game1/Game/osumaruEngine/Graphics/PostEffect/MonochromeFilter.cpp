#include "engineStdafx.h"
#include "MonochromeFilter.h"
#include "../../Engine.h"
#include "../VertexCommon.h"
#include "../EffectManager.h"

MonochromeFilter::MonochromeFilter()
{
	m_isActive = false;
}

MonochromeFilter::~MonochromeFilter()
{

}

void MonochromeFilter::Init(bool isActive)
{
	m_isActive = isActive;
	if (!m_isActive)
	{
		return;
	}
	const int vertexNum = 4;
	VERTEX_PT vertexBuffer[vertexNum] =
	{
		{ -1.0f,  1.0f, 0.0, 1.0f, 0.0f, 0.0f },
		{  1.0f,  1.0f, 0.0, 1.0f, 1.0f, 0.0f },
		{  1.0f, -1.0f, 0.0, 1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 0.0, 1.0f, 0.0f, 1.0f }
	};
	const int indexNum = 6;
	WORD indexBuffer[indexNum] = { 0, 1, 2, 0, 2, 3};
	m_primitive.Create(vertex_PT, vertexBuffer, vertexNum, sizeof(VERTEX_PT), indexBuffer, indexNum, Primitive::enIndex16, Primitive::enTypeTriangleList);
	m_pEffect = GetEffectManager().LoadEffect("Assets/shader/MonochromeFilter.fx");
}

void MonochromeFilter::Draw()
{
	if (!m_isActive)
	{
		return;
	}
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	LPDIRECT3DTEXTURE9 texture = GetMainRenderTarget().GetTexture();
	GetEngine().SwitchingRenderTarget();
	device->SetRenderTarget(0, GetMainRenderTarget().GetRenderTarget());
	device->SetDepthStencilSurface(GetMainRenderTarget().GetDepthStencilBuffer());
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	DWORD zenableBackUp;
	DWORD alphaBlendBackUp;
	device->GetRenderState(D3DRS_ZENABLE, &zenableBackUp);
	device->GetRenderState(D3DRS_ALPHABLENDENABLE, &alphaBlendBackUp);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pEffect->SetTechnique("Monochrome");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	m_pEffect->SetTexture("g_tex", texture);
	m_pEffect->CommitChanges();
	device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
	device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
	device->SetIndices(m_primitive.GetIndexBuffer());
	device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
	m_pEffect->EndPass();
	m_pEffect->End();
	device->SetRenderState(D3DRS_ZENABLE, zenableBackUp);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaBlendBackUp);
}
