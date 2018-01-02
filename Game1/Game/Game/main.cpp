#include "stdafx.h"
#include "GameCamera\GameCamera.h"
#include "Scene/GameScene.h"
#include "Scene\Fade.h"
#include "../Game/GhostPlayer/GhostDataList.h"
#include "Scene\TitleScene.h"


int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//Direct3DÇèâä˙âª
	GetEngine().InitD3D(hInst);
	New<TitleScene>(0);
	g_pFade = New<Fade>(priorityMax - 1);
	g_pFade->Init();
	g_ghostDataList = New<GhostDataList>(lastPriority);
	GetEngine().GameLoop();
	return 0;
}