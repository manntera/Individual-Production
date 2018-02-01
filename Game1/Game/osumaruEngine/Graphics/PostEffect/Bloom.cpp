#include "engineStdafx.h"
#include "Bloom.h"
#include "../../Engine.h"
#include "../EffectManager.h"
#include "../VertexCommon.h"

Bloom::Bloom()
{
	for (int i = 0; i < BLUR_RANGE; i++)
	{
		m_weight[i] = 1.0f;
	}
	SetWeight(1.0f);
	m_isActive = false;
}

Bloom::~Bloom()
{

}

void Bloom::SetWeight(float rate)
{
	float total = 0.0f;
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

void Bloom::Init(bool isActive)
{
	m_isActive = isActive;
	if (!m_isActive)
	{
		return;
	}
	m_luminanceTarget.Create(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, D3DFMT_A16B16G16R16F, D3DFMT_D16);
	m_combineTarget.Create(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, D3DFMT_A16B16G16R16F, D3DFMT_D16);
	for (int i = 0; i < DOWN_SAMPLING_NUM; i++)
	{
		m_downSamplingTarget[i][0].Create(FRAME_BUFFER_WIDTH >> i + 1, FRAME_BUFFER_HEIGHT >> i, D3DFMT_A16B16G16R16F, D3DFMT_D16);
		m_downSamplingTarget[i][1].Create(FRAME_BUFFER_WIDTH >> i + 1, FRAME_BUFFER_HEIGHT >> i + 1, D3DFMT_A16B16G16R16F, D3DFMT_D16);
	}
	VERTEX_PT vertexBuffer[4] =
	{
		{ -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{  1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{  1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f }
	};
	WORD indexbuffer[6] = { 0, 1, 2, 0, 2, 3 };
	m_primitive.Create(vertex_PT, vertexBuffer, 4, sizeof(VERTEX_PT), indexbuffer, 6, Primitive::enIndex16, Primitive::enTypeTriangleList);
	m_pEffect = GetEngine().GetEffectManager().LoadEffect("Assets/shader/bloom.fx");
}

void Bloom::Draw()
{
	if (!m_isActive)
	{
		return;
	}
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	DWORD zenableBackup;
	device->GetRenderState(D3DRS_ZENABLE, &zenableBackup);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	//輝度抽出
	{
		device->SetRenderTarget(0, m_luminanceTarget.GetRenderTarget());
		device->SetDepthStencilSurface(m_luminanceTarget.GetDepthStencilBuffer());
		device->BeginScene();
		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		m_pEffect->SetTechnique("LuminanceExtraction");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		m_pEffect->SetTexture("g_sceneTexture", GetMainRenderTarget().GetTexture());
		m_pEffect->CommitChanges();
		device->SetIndices(m_primitive.GetIndexBuffer());
		device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
		device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
		device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
		m_pEffect->EndPass();
		m_pEffect->End();
		device->EndScene();
	}
	for (int i = 0; i < DOWN_SAMPLING_NUM; i++)
	{
		//X方向へのブラー
		{
			device->SetRenderTarget(0, m_downSamplingTarget[i][0].GetRenderTarget());
			device->SetDepthStencilSurface(m_downSamplingTarget[i][0].GetDepthStencilBuffer());
			device->BeginScene();
			m_pEffect->SetTechnique("XBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float offset[2] = {0.0f};
			float size[2] = { 0.0f };
			if (i == 0)
			{
				m_pEffect->SetTexture("g_sceneTexture", m_luminanceTarget.GetTexture());
				offset[0] = 16.0f / m_luminanceTarget.GetWidth();
				offset[1] = 0.0f;
				size[0] = m_luminanceTarget.GetWidth();
				size[1] = m_luminanceTarget.GetHeight();
			}
			else
			{
				m_pEffect->SetTexture("g_sceneTexture", m_downSamplingTarget[i - 1][1].GetTexture());
				offset[0] = 16.0f / m_downSamplingTarget[i - 1][1].GetWidth();
				offset[1] = 0.0f;
				size[0] = m_downSamplingTarget[i - 1][1].GetWidth();
				size[1] = m_downSamplingTarget[i - 1][1].GetHeight();
			}
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
			device->SetRenderTarget(0, m_downSamplingTarget[i][1].GetRenderTarget());
			device->SetDepthStencilSurface(m_downSamplingTarget[i][1].GetDepthStencilBuffer());
			device->BeginScene();
			m_pEffect->SetTechnique("YBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			m_pEffect->SetTexture("g_sceneTexture", m_downSamplingTarget[i][0].GetTexture());
			float offset[2] = { 0.0f, 16.0f / m_downSamplingTarget[i][0].GetWidth() };
			float size[2] = { m_downSamplingTarget[i][0].GetWidth(), m_downSamplingTarget[i][0].GetHeight() };
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
	}
	//ぼかし合成
	{
		
		device->SetRenderTarget(0, m_combineTarget.GetRenderTarget());
		device->SetDepthStencilSurface(m_combineTarget.GetDepthStencilBuffer());
		device->BeginScene();
		m_pEffect->SetTechnique("Combine");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		m_pEffect->SetTexture("g_downTexture0", m_downSamplingTarget[0][1].GetTexture());
		m_pEffect->SetTexture("g_downTexture1", m_downSamplingTarget[1][1].GetTexture());
		m_pEffect->SetTexture("g_downTexture2", m_downSamplingTarget[2][1].GetTexture());
		m_pEffect->SetTexture("g_downTexture3", m_downSamplingTarget[3][1].GetTexture());
		m_pEffect->SetTexture("g_downTexture4", m_downSamplingTarget[4][1].GetTexture());
		m_pEffect->CommitChanges();
		device->SetIndices(m_primitive.GetIndexBuffer());
		device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
		device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
		device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
		m_pEffect->EndPass();
		m_pEffect->End();
		device->EndScene();
	}

	//最終合成
	{
		device->SetRenderTarget(0, GetMainRenderTarget().GetRenderTarget());
		device->SetDepthStencilSurface(GetMainRenderTarget().GetDepthStencilBuffer());
		DWORD alphaEnableBackup, srcBlendBackup, destBlendBackup;
		device->GetRenderState(D3DRS_ALPHABLENDENABLE, 
			&alphaEnableBackup);
		device->GetRenderState(D3DRS_SRCBLEND, &srcBlendBackup);
		device->GetRenderState(D3DRS_DESTBLEND, &destBlendBackup);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		device->BeginScene();
		m_pEffect->SetTechnique("Final");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		m_pEffect->SetTexture("g_sceneTexture", m_combineTarget.GetTexture());
		m_pEffect->CommitChanges();
		device->SetIndices(m_primitive.GetIndexBuffer());
		device->SetVertexDeclaration(m_primitive.GetVertexDecaration());
		device->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, m_primitive.GetVertexStride());
		device->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, m_primitive.GetVertexNum(), 0, m_primitive.GetPolygonNum());
		m_pEffect->EndPass();
		m_pEffect->End();
		device->EndScene();
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaEnableBackup);
		device->SetRenderState(D3DRS_SRCBLEND, srcBlendBackup);
		device->SetRenderState(D3DRS_DESTBLEND, destBlendBackup);
	}
	device->SetRenderState(D3DRS_ZENABLE, zenableBackup);

}