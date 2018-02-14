#include "stdafx.h"
#include "GameCamera\GameCamera.h"
#include "Scene/GameScene.h"
#include "Scene\Fade.h"
#include "../Game/GhostPlayer/GhostDataListManager.h"
#include "Scene\TitleScene.h"
#include "Scene/GameClearScene.h"
#include "Scene\GameOverScene.h"
#include "Scene/TimeAttackResult.h"

using namespace std;
int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//Direct3D��������
	GetEngine().InitD3D(hInst);
	New<TitleScene>(0);
	TimeAttackResult::TimeDataRead();
	GetGhostDataListManager().GhostDataRead();
	GetFade().Init();
	GetEngine().GameLoop();
	TimeAttackResult::TimeDataSave();
	GetGhostDataListManager().GhostDataSave();
	return 0;
}