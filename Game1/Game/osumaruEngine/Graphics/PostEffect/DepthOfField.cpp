#include "engineStdafx.h"
#include "DepthOfField.h"
#include "../VertexCommon.h"
#include "../EffectManager.h"
#include "../../Engine.h"

DepthOfField::DepthOfField()
{
	m_isActive = false;
	float total = 0.0f;
	float rate = 1.0f;
	for (int i = 0; i < 8; i++)
	{
		m_weight[i] = expf(-0.5f * float(i * i) / rate);
		total += 2.0f * m_weight[i];
	}
	for (int i = 0; i < 8; i++)
	{
		m_weight[i] /= total;
	}
}

DepthOfField::~DepthOfField()
{

}

void DepthOfField::Init(bool isActive)
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
		{ 1.0f,  1.0f, 0.0, 1.0f, 1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0, 1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 0.0, 1.0f, 0.0f, 1.0f }
	};
	const int indexNum = 6;
	WORD indexBuffer[indexNum] = { 0, 1, 2, 0, 2, 3 };
	m_primitive.Create(vertex_PT, vertexBuffer, vertexNum, sizeof(VERTEX_PT), indexBuffer, indexNum, Primitive::enIndex16, Primitive::enTypeTriangleList);
	m_pEffect = GetEffectManager().LoadEffect("Assets/shader/DepthOfField.fx");
	m_depthTarget.Create(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, D3DFMT_R32F, D3DFMT_D16);
	m_blur[0].Create(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, D3DFMT_A8R8G8B8, D3DFMT_D16);
	m_blur[1].Create(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, D3DFMT_A8R8G8B8, D3DFMT_D16);
}

void DepthOfField::Draw()
{
	if (!m_isActive)
	{
		return;
	}
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	//X方向へのブラー
	{
		device->SetRenderTarget(0, m_blur[0].GetRenderTarget());
		device->SetDepthStencilSurface(m_blur[0].GetDepthStencilBuffer());
		device->BeginScene();
		m_pEffect->SetTechnique("XBlur");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		float offset[2] = { 0.0f };
		float size[2] = { 0.0f };
		m_pEffect->SetTexture("g_sceneTexture", GetMainRenderTarget().GetTexture());
		offset[0] = 16.0f / GetMainRenderTarget().GetWidth();
		offset[1] = 0.0f;
		size[0] = GetMainRenderTarget().GetWidth();
		size[1] = GetMainRenderTarget().GetHeight();
		m_pEffect->SetValue("g_offset", offset, sizeof(offset));
		m_pEffect->SetValue("g_weight", m_weight, sizeof(m_weight));
		m_pEffect->SetValue("g_sceneTextureSize", size, sizeof(size));
		m_pEffect->CommitChanges();
		device->SetIndices(m_primitive.GetIndexBuffer());
		device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
		device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
		device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
		m_pEffect->EndPass();
		m_pEffect->End();
		device->EndScene();
	}
	//Y方向へのブラー
	{
		device->SetRenderTarget(0, m_blur[1].GetRenderTarget());
		device->SetDepthStencilSurface(m_blur[1].GetDepthStencilBuffer());
		device->BeginScene();
		m_pEffect->SetTechnique("YBlur");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		m_pEffect->SetTexture("g_sceneTexture", m_blur[0].GetTexture());
		float offset[2] = { 0.0f, 16.0f / m_blur[0].GetWidth() };
		float size[2] = { m_blur[0].GetWidth(), m_blur[0].GetHeight() };
		m_pEffect->SetValue("g_offset", offset, sizeof(offset));
		m_pEffect->SetValue("g_weight", m_weight, sizeof(m_weight));
		m_pEffect->SetValue("g_sceneTextureSize", size, sizeof(size));
		m_pEffect->CommitChanges();
		device->SetIndices(m_primitive.GetIndexBuffer());
		device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
		device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
		device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
		m_pEffect->EndPass();
		m_pEffect->End();
		device->EndScene();
	}
	//合成して描画
	{
		LPDIRECT3DTEXTURE9 texture = GetMainRenderTarget().GetTexture();
		device->SetRenderTarget(0, GetMainRenderTarget().GetRenderTarget());
		device->SetDepthStencilSurface(GetMainRenderTarget().GetDepthStencilBuffer());
		DWORD zenableBackUp, alphaBlendBackUp, blendSrcBackup, blendDestBackup;
		device->GetRenderState(D3DRS_ZENABLE, &zenableBackUp);
		device->GetRenderState(D3DRS_ALPHABLENDENABLE, &alphaBlendBackUp);
		device->GetRenderState(D3DRS_SRCBLEND, &blendSrcBackup);
		device->GetRenderState(D3DRS_DESTBLEND, &blendDestBackup);
		device->SetRenderState(D3DRS_ZENABLE, FALSE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pEffect->SetTechnique("Combine");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		float offset[2] = { 0.5f / m_blur[1].GetWidth(), 0.5f / m_blur[1].GetHeight() };
		m_pEffect->SetTexture("g_sceneTexture", texture);
		m_pEffect->SetTexture("g_blurTexture", m_blur[1].GetTexture());
		m_pEffect->SetTexture("g_depthTexture", m_depthTarget.GetTexture());
		m_pEffect->SetFloatArray("g_offset", offset, 2);
		m_pEffect->CommitChanges();
		device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
		device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
		device->SetIndices(m_primitive.GetIndexBuffer());
		device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
		m_pEffect->EndPass();
		m_pEffect->End();
		device->SetRenderState(D3DRS_ZENABLE, zenableBackUp);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaBlendBackUp);
		device->SetRenderState(D3DRS_SRCBLEND, blendSrcBackup);
		device->SetRenderState(D3DRS_DESTBLEND, blendDestBackup);
	}
}