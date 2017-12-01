#include "engineStdafx.h"
#include "Engine.h"
#include "graphics/EffectManager.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		GetEngine().Release();
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Engine::Engine()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_effectManager = nullptr;
	m_physicsWorld = nullptr;
}

Engine::~Engine()
{
	Release();
}


void Engine::InitD3D(HINSTANCE& hInst)
{

	UNREFERENCED_PARAMETER(hInst);
	//ウィンドウクラスを作成
	m_wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,0L,0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Game", NULL
	};
	//ウィンドウクラスを登録
	RegisterClassEx(&m_wc);

	//ウィンドウを作成
	HWND hWnd = CreateWindow("Game", "Game",
		WS_OVERLAPPEDWINDOW, 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT,
		NULL, NULL, m_wc.hInstance, NULL);

	//D3Dオブジェクトを作成する
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	//D3Dデバイスを作成するためのパラメータを設定する。
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//D3Dデバイスを作成する。
	HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice);
	if (hr == D3DERR_INVALIDCALL)
	{
		std::abort();
	}
	m_effectManager = new EffectManager;
	m_physicsWorld = new PhysicsWorld;
	m_physicsWorld->Init();
	m_shadowMap.Create(2048, 2048);
	m_shadowMap.SetLightCameraTarget({ 0.0f, 00.0f, 0.0f });
	m_shadowMap.SetLightCameraPosition({ 0.0f, 20.0f, 0.0f });
	m_shadowMap.SetLightCameraUp({ 1.0f, 0.0f, 0.0f });
	m_objectManager.Init();
	m_soundEngine.Init();
	m_renderTarget.Create(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, D3DFMT_A8R8G8B8, D3DFMT_D16);
	m_postEffect.Init();
	// show the window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

void Engine::GameLoop()
{
	//ゲームループ
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
			m_objectManager.Execute(m_postEffect);
			m_physicsWorld->Update();
			m_shadowMap.Update();
			m_pad.Update();

		}
	}

	UnregisterClass("shader Tutorial", m_wc.hInstance);
}