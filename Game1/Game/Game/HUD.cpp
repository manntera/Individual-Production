#include "stdafx.h"
#include "HUD.h"
#include "GameCamera.h"

void HUD::Init()
{
	sprite.Init("../Game/Assets/sprite/Texture.png");
	sprite.SetSize(D3DXVECTOR2(100.0f, 100.0f));
	light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	skinModelData.LoadModelData("../Game/Assets/modelData/snowman1-3-2.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);

	D3DXQuaternionIdentity(&rotation);
	trans = { 0.0f, 17.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
	capsuleCollider.Create(1.0f, 1.0f);
	RigidBodyInfo RBInfo;
	RBInfo.collider = &capsuleCollider;
	RBInfo.pos = trans;
	RBInfo.mass = 1.0f;
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	RBInfo.rot = rot;
	rigidBody.Create(RBInfo);
	rigidBody.GetBody()->getWorldTransform().setOrigin(btVector3(trans.x, trans.y, trans.z));
	//rigidBody.GetBody()->setGravity(btVector3(0.0f, 0.0f, 0.0f));
}

void HUD::Update()
{
	btRigidBody* rig = rigidBody.GetBody();
	btVector3 moveSpeed(0.0f, 0.0f, 0.0f);
	float x = moveSpeed.x();
	float z = moveSpeed.z();
	if (GetAsyncKeyState(VK_LEFT))
	{
		x -= 3.0f;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		x += 3.0f;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		z += 3.0f;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		z -= 3.0f;
	}
	moveSpeed.setX(x);
	moveSpeed.setZ(z);
	rig->applyForce(moveSpeed, btVector3(0.0f, 0.0f, 0.0));

	trans = D3DXVECTOR3(rig->getWorldTransform().getOrigin());
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void HUD::Render()
{
	//sprite.Draw();
	skinModel.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
}

