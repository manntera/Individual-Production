#include "stdafx.h"
#include "test.h"
#include "GameCamera\GameCamera.h"
#include "Scene\GameScene\GameScene.h"

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
	g_gameScene->Init();
	GetEngine().GameLoop();
	return 0;
}