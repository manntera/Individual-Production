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
	RenderTarget	m_depthTarget;	//�[�x�������ݗp�̃����_�����O�^�[�Q�b�g
	RenderTarget	m_blur[2];			//�u���[��������ڂ����p�̃����_�����O�^�[�Q�b�g
	float			m_weight[8];
	LPD3DXEFFECT	m_pEffect;		//
	Primitive		m_primitive;
};
