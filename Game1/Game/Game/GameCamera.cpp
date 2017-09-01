#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::Init()
{
	camera.Init();
	camera.SetPosition({ 0.0, 0.0f, 10.0f });
	camera.SetTarget({0.0f, 0.0f, 0.0f});
}

void GameCamera::Update()
{
	camera.Update();
}