#include "stdafx.h"
#include "test.h"
#include "GameCamera.h"

void Test::Init()
{
	light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	skinModelData.LoadModelData("../Game/Assets/modelData/ground.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 trans;
	D3DXVECTOR3 scale;
	trans = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	meshCollider.CreateFromSkinModel(&skinModel, &skinModel.GetWorldMatrix());
	RigidBodyInfo RBInfo;
	RBInfo.collider = &meshCollider;
	RBInfo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RBInfo.mass = 0.0f;
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	RBInfo.rot = rot;
	rigidBody.Create(RBInfo);
	//rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(0.0f, 0.0f, 0.0f));
}

void Test::Update()
{
	D3DXQUATERNION rotation;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 trans;
	D3DXVECTOR3 scale;
	trans = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void Test::Render()
{
	skinModel.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
}