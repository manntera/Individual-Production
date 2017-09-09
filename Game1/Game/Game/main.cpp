#include "stdafx.h"
#include "HUD.h"
#include "test.h"
#include "GameCamera.h"


int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{


	//Direct3D‚ğ‰Šú‰»
	GetEngine().InitD3D(hInst);
	Test* test = New<Test>();
	test->Init();
	HUD* hud = New<HUD>();
	hud->Init();
	g_camera = New<GameCamera>();
	g_camera->Init();
	GetEngine().GameLoop();

	return 0;
}