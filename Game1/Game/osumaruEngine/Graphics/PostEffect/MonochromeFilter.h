#pragma once
#include "../Primitive.h"
#include "../RenderTarget.h"

class MonochromeFilter
{
public:
	MonochromeFilter();

	~MonochromeFilter();

	void Init();

	void Draw();

private:
	Primitive		m_primitive;
	//RenderTarget	m_renderTarget;
	LPD3DXEFFECT	m_pEffect;
};