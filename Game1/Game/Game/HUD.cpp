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
	trans = { 0.0f, 7.0f, 0.0f };
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
	characterController.Init(1.0f, 1.0f, trans);
	characterController.SetMoveSpeed({0.0f, 0.0f, 0.0f});
	characterController.SetGravity(0.0f);
}

void HUD::Update()
{
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	//if (GetPad().IsPressButton(padButtonLStickPush))
	//{
	//	moveSpeed.x = -30.0f;
	//}
	//else if(GetPad().IsPressButton(padButtonRStickPush))
	//{
	//	moveSpeed.x = 30.0f;
	//}

	//if (0 < GetPad().GetLeftTrigger())
	//{
	//	moveSpeed.z = 30.0f;
	//}
	//else if (0 < GetPad().GetRightTrigger())
	//{
	//	moveSpeed.z = -30.0f;
	//}
	moveSpeed.x = GetPad().GetRightStickX() * 30.0f;
	moveSpeed.z = GetPad().GetRightStickY() * 30.0f;

	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	trans = characterController.GetPosition();
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void HUD::Render()
{
	//sprite.Draw();
	skinModel.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
}

