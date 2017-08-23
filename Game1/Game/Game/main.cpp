#include "stdafx.h"
#include "HUD.h"

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
	hud->Init(GetEngine().GetDevice());
	GetEngine().GameLoop();

	return 0;
}