#include "stdafx.h"
#include "GameCamera.h"


GameCamera *g_camera = nullptr;

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()

{

}

void GameCamera::Init()
{
	camera.Init();
	camera.SetPosition({ 0.0, 40.0f, -40.0f });
	camera.SetTarget({0.0f, 0.0f, 0.0f});
}

void GameCamera::Update()
{

	camera.Update();
}