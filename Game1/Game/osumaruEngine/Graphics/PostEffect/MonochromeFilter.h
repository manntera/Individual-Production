#pragma once

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
	bool				m_isActive;
};