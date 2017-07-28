#pragma once
#include "common.h"
const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;

class Engine
{
public:
	//DirectXÇèâä˙âª
	void InitD3D(HWND hWnd);

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
};