#include "stdafx.h"
#include "test.h"
#include "GameCamera/GameCamera.h"
#include "Scene\GameScene\GameScene.h"

void Test::Init()
{
	light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	skinModelData.LoadModelData("Assets/modelData/Box.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.m_isShadowMapReceiver = true;
	D3DXQuaternionIdentity(&rotation);
	D3DXVECTOR3 scale;
	trans = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	//meshCollider.CreateFromSkinModel(&skinModel, NULL);
	boxCollider.Create(btVector3(10.0f, 3.0f, 10.0f));
	RigidBodyInfo RBInfo;
	RBInfo.collider = &boxCollider;
	RBInfo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RBInfo.mass = 0.0f;

	D3DXQuaternionIdentity(&rotation);
	D3DXQUATERNION multi;
	float angle = 0.0f / 180.0f * cPI;
	D3DXQuaternionRotationAxis(&multi, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), angle);
	D3DXQuaternionMultiply(&rotation, &rotation, &multi);
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	RBInfo.rot = rotation;
	rigidBody.Create(RBInfo);
	rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(trans.x, trans.y, trans.z));
	rigidBody.GetBody()->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
}

void Test::Update()
{

	D3DXVECTOR3 scale;
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void Test::Render(int num)
{
	skinModel.Draw(&g_gameScene->GetCamera()->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera()->GetCamera().GetProjectionMatrix(), num);
}