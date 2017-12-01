#include "engineStdafx.h"
#include "MonochromeFilter.h"
#include "../../Engine.h"
#include "../VertexCommon.h"
#include "../EffectManager.h"

MonochromeFilter::MonochromeFilter()
{

}

MonochromeFilter::~MonochromeFilter()
{

}

void MonochromeFilter::Init()
{
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
	//LPDIRECT3DSURFACE9 renderTargetBackup;
	//LPDIRECT3DSURFACE9 depthStencilBackup;
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	//device->GetRenderTarget(0, &renderTargetBackup);
	//device->GetDepthStencilSurface(&depthStencilBackup);
	//device->SetRenderTarget(0, m_renderTarget.GetRenderTarget());
	//device->SetDepthStencilSurface(m_renderTarget.GetDepthStencilBuffer());
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pEffect->SetTechnique("Monochrome");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	m_pEffect->SetTexture("g_tex", GetMainRenderTarget().GetTexture());
	m_pEffect->CommitChanges();
	device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
	device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
	device->SetIndices(m_primitive.GetIndexBuffer());
	device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
	m_pEffect->EndPass();
	m_pEffect->End();
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//device->SetRenderTarget(0, renderTargetBackup);
	//device->SetDepthStencilSurface(depthStencilBackup);
	//renderTargetBackup->Release();
	//depthStencilBackup->Release();
}
