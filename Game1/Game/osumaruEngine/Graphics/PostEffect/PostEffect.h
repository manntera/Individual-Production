#pragma once
#include "MonochromeFilter.h"
#include "Bloom.h"

class PostEffect
{
public:
	PostEffect();

	~PostEffect();

	void Init();

	void Draw();
private:
	Bloom				m_bloom;
	MonochromeFilter	m_monochrome;
	Primitive			m_primitive;
	LPD3DXEFFECT		m_pEffect;
	LPDIRECT3DSURFACE9	m_frameBuffer;
	LPDIRECT3DSURFACE9	m_depthBuffer;
};