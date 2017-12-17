#pragma once
#include "MonochromeFilter.h"
#include "Bloom.h"
#include "DepthOfField.h"

class PostEffect
{
public:
	PostEffect();

	~PostEffect();

	void Init();

	void Draw();

	DepthOfField& GetDepthOfField()
	{
		return m_dof;
	}
private:
	Bloom				m_bloom;
	MonochromeFilter	m_monochrome;
	DepthOfField		m_dof;
	Primitive			m_primitive;
	LPD3DXEFFECT		m_pEffect;
	LPDIRECT3DSURFACE9	m_frameBuffer;
	LPDIRECT3DSURFACE9	m_depthBuffer;
};