#include "stdafx.h"


int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{

	//Direct3D‚ğ‰Šú‰»
	GetEngine().InitD3D(hInst);

	GetEngine().GameLoop();

	return 0;
}