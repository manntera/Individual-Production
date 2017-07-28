#include "stdafx.h"
int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	UNREFERENCED_PARAMETER(hInst);

	//ウィンドウクラスを作成
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,0L,0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Game", NULL
	};
	//ウィンドウクラスを登録
	RegisterClassEx(&wc);

	//ウィンドウを作成
	HWND hWnd = CreateWindow("Game", "Game",
		WS_OVERLAPPEDWINDOW, 100, 100, FRAME_BUFFER_WIDTH + 100, FRAME_BUFFER_HEIGHT + 100,
		NULL, NULL, wc.hInstance, NULL);
	//Direct3Dを初期化
	InitD3D(hWnd);

	// show the window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//ここからゲーム関係の初期化
	Init();

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
			Update();
			Render();
		}
	}
	UnregisterClass("shader Tutorial", wc.hInstance);

	return 0;
}