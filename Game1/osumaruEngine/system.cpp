#include "common.h"
#include "system.h"
#include "graphics/EffectManager.h"



//DirectXを初期化
void InitD3D(HWND hWnd)
{
	//D3Dオブジェクトを作成する
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//D3Dデバイスを作成するためのパラメータを設定する。
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//D3Dデバイスを作成する。
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice);
	g_effectManager = new EffectManager;
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		if (g_pD3DDevice != NULL)
		{
			g_pD3DDevice->Release();
		}
		if (g_pD3D != NULL)
		{
			g_pD3D->Release();
		}
		Terminate();
		PostQuitMessage(0);
		return 0;
	}
}