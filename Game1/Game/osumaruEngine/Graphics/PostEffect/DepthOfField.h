#pragma once

class DepthOfField : Uncopyable
{
public:

	void Init();
private:
	RenderTarget	m_depthTarget;	//深度書き込み用のレンダリングターゲット
	RenderTarget	m_blur;			//ブラーをかけるぼかし用のレンダリングターゲット
	LPD3DXEFFECT	m_pEffect;		//
	Primitive		m_primitive;
};
