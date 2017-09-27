#include "stdafx.h"
#include "GameCamera\GameCamera.h"
#include "Scene/GameScene.h"
#include "Scene\Fade.h"



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
	g_pFade = New<Fade>();
	g_pFade->Init();
	GetEngine().GameLoop();
	return 0;
}