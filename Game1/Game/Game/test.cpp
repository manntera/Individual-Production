#include "stdafx.h"
#include "test.h"
#include "GameCamera/GameCamera.h"
#include "Scene\GameScene\GameScene.h"

void Test::Init()
{
	light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	skinModelData.LoadModelData("../Game/Assets/modelData/Box.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 scale;
	trans = { 10.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	meshCollider.CreateFromSkinModel(&skinModel, NULL);
	RigidBodyInfo RBInfo;
	RBInfo.collider = &meshCollider;
	RBInfo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RBInfo.mass = 0.0f;

	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	RBInfo.rot = rot;
	rigidBody.Create(RBInfo);
	rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(trans.x, trans.y, trans.z));
}

void Test::Update()
{
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 scale;
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void Test::Render()
{
	skinModel.Draw(&g_gameScene->GetCamera()->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera()->GetCamera().GetProjectionMatrix());
}