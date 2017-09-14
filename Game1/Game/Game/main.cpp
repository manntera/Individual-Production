#include "stdafx.h"
#include "test.h"
#include "GameCamera\GameCamera.h"
#include "Scene\GameScene\GameScene.h"
extern Camera* g_pCamera;

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
	g_pCamera = &g_gameScene->GetCamera()->GetCamera();
	GetEngine().GameLoop();
	return 0;
}