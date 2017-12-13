#pragma once
#include "../Primitive.h"
#include "../RenderTarget.h"

class MonochromeFilter
{
public:
	MonochromeFilter();

	~MonochromeFilter();

	void Init(bool isActive);

	void Draw();

private:
	Primitive		m_primitive;
	LPD3DXEFFECT	m_pEffect;
	LPDIRECT3DSURFACE9	m_backBuffer;
	LPDIRECT3DSURFACE9	m_depthBuffer;
	bool				m_isActive;
};