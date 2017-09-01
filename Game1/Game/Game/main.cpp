#include "stdafx.h"
#include "HUD.h"
#include "GameCamera.h"

GameCamera *g_camera = nullptr;

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{


	//Direct3D‚ğ‰Šú‰»
	GetEngine().InitD3D(hInst);
	HUD* hud = New<HUD>();
	g_camera = New<GameCamera>();
	g_camera->Init();
	hud->Init(GetEngine().GetDevice());
	GetEngine().GameLoop();

	return 0;
}