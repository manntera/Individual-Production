#include "stdafx.h"
#include "GameCamera\GameCamera.h"
#include "Scene/GameScene.h"

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{


	//Direct3D‚ğ‰Šú‰»
	GetEngine().InitD3D(hInst);
	g_gameScene = New<GameScene>();
	GetEngine().GameLoop();
	return 0;
}