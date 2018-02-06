#include "stdafx.h"
#include "GameCamera\GameCamera.h"
#include "Scene/GameScene.h"
#include "Scene\Fade.h"
#include "../Game/GhostPlayer/GhostDataListManager.h"
#include "Scene\TitleScene.h"
#include "Scene/GameClearScene.h"
#include "Scene\GameOverScene.h"
#include "Scene/TimeAttackResult.h"

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
	TimeAttackResult::TimeInit();
	GetFade().Init();
	GetEngine().GameLoop();
	return 0;
}