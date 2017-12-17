#include "engineStdafx.h"
#include "PostEffect.h"
#include "../../Engine.h"
#include "../VertexCommon.h"
#include "../EffectManager.h"

PostEffect::PostEffect()
{
	m_frameBuffer = nullptr;
	m_depthBuffer = nullptr;
}

PostEffect::~PostEffect()
{
	if (m_frameBuffer != nullptr)
	{
		m_frameBuffer->Release();
		m_frameBuffer = nullptr;
	}
	if (m_depthBuffer != nullptr)
	{
		m_depthBuffer->Release();
		m_depthBuffer = nullptr;
	}

}

void PostEffect::Init()
{
	m_bloom.Init(false);
	m_bloom.SetWeight(30.0f);
	m_monochrome.Init(false);
	m_dof.Init(false);
	const int vertexNum = 4;
	VERTEX_PT vertexBuffer[vertexNum] =
	{
		{ -1.0f,  1.0f, 0.0, 1.0f, 0.0f, 0.0f },
		{ 1.0f,  1.0f, 0.0, 1.0f, 1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0, 1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 0.0, 1.0f, 0.0f, 1.0f }
	};
	const int indexNum = 6;
	WORD indexBuffer[indexNum] = { 0, 1, 2, 0, 2, 3 };
	m_primitive.Create(vertex_PT, vertexBuffer, vertexNum, sizeof(VERTEX_PT), indexBuffer, indexNum, Primitive::enIndex16, Primitive::enTypeTriangleList);
	m_pEffect = GetEffectManager().LoadEffect("Assets/shader/PostEffect.fx");
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	device->GetRenderTarget(0, &m_frameBuffer);
	device->GetDepthStencilSurface(&m_depthBuffer);
	
}

void PostEffect::Draw()
{
	m_bloom.Draw();
	m_monochrome.Draw();
	m_dof.Draw();
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	device->SetRenderTarget(0, m_frameBuffer);
	device->SetDepthStencilSurface(m_depthBuffer);
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	DWORD zstateBackUp;
	device->GetRenderState(D3DRS_ZENABLE, &zstateBackUp);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pEffect->SetTechnique("PostEffect");
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

	device->SetRenderState(D3DRS_ZENABLE, zstateBackUp);
}