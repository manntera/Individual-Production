#pragma once

class DepthOfField : Uncopyable
{
public:

	void Init();
private:
	RenderTarget	m_depthTarget;	//�[�x�������ݗp�̃����_�����O�^�[�Q�b�g
	RenderTarget	m_blur;			//�u���[��������ڂ����p�̃����_�����O�^�[�Q�b�g
	LPD3DXEFFECT	m_pEffect;		//
	Primitive		m_primitive;
};
