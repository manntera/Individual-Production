#pragma once

class DepthOfField : Uncopyable
{
public:
	DepthOfField();

	~DepthOfField();

	void Init(bool isActive);

	void Draw();

	RenderTarget& GetDepthRendertarget()
	{
		return m_depthTarget;
	}

private:
	bool			m_isActive;
	RenderTarget	m_depthTarget;	//深度書き込み用のレンダリングターゲット
	RenderTarget	m_blur[2];			//ブラーをかけるぼかし用のレンダリングターゲット
	float			m_weight[8];
	LPD3DXEFFECT	m_pEffect;		//
	Primitive		m_primitive;
};
