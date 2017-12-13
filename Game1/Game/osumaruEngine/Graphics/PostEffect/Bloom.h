#pragma once

const int g_downSamplingNum = 5;

class Bloom : Uncopyable
{
public:
	Bloom();

	~Bloom();

	void Init(bool isActive);

	void Draw();

	void SetWeight(float rate);
private:
	RenderTarget m_downSamplingTarget[g_downSamplingNum][2];
	RenderTarget m_luminanceTarget;
	RenderTarget m_combineTarget;
	LPD3DXEFFECT m_pEffect;
	float		 m_weight[8];
	Primitive	 m_primitive;
	bool		 m_isActive;
};