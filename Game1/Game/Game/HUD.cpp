#include "stdafx.h"
#include "HUD.h"
#include "GameCamera.h"

extern GameCamera *g_camera;
void HUD::Init(LPDIRECT3DDEVICE9 pDevice)
{
	//sprite.Init("../Game/Assets/sprite/Texture.jpg");
	light.SetAmbiemtLight({ 1.0f, 1.0f, 1.0f, 1.0f });
	skinModelData.LoadModelData("../Game/Assets/modelData/snowman1-3-2.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	D3DXQuaternionIdentity(&rotation);
}

void HUD::Update()
{
	//D3DXVECTOR2 position = sprite.GetPosition();
	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	position.x -= 10.0f;
	//}
	//else if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	position.x += 10.0f;
	//}
	//if (GetAsyncKeyState(VK_DOWN))
	//{
	//	D3DXVECTOR2 size = sprite.GetSize();
	//	size *= 0.99f;
	//	sprite.SetSize(size);
	//}
	//else if (GetAsyncKeyState(VK_UP))
	//{
	//	D3DXVECTOR2 size = sprite.GetSize();
	//	size /= 0.99f;
	//	sprite.SetSize(size);
	//}
	//sprite.SetPosition(position);
	D3DXQUATERNION rotX;
	D3DXQUATERNION rotY;
	D3DXQuaternionIdentity(&rotX);
	D3DXQuaternionIdentity(&rotY);
	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleSpeed = 0.1f;
	if (GetAsyncKeyState(VK_LEFT))
	{
		angleY += angleSpeed;
		D3DXQuaternionRotationAxis(&rotY, &(D3DXVECTOR3(0.0f, 1.0f, 0.0f)), angleY);
		D3DXQuaternionMultiply(&rotation, &rotation, &rotY);
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		angleY -= angleSpeed;
		D3DXQuaternionRotationAxis(&rotY, &(D3DXVECTOR3(0.0f, 1.0f, 0.0f)), angleY);
		D3DXQuaternionMultiply(&rotation, &rotation, &rotY);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		angleX += angleSpeed;
		D3DXQuaternionRotationAxis(&rotX, &(D3DXVECTOR3(1.0f, 0.0f, 0.0f)), angleX);
		D3DXQuaternionMultiply(&rotation, &rotation, &rotX);
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		angleX -= angleSpeed;
		D3DXQuaternionRotationAxis(&rotX, &(D3DXVECTOR3(1.0f, 0.0f, 0.0f)), angleX);
		D3DXQuaternionMultiply(&rotation, &rotation, &rotX);
	}

	D3DXVECTOR3 trans;
	D3DXVECTOR3 scale;
	trans = { 0.0f, 0.0f, 0.0f};
	scale = { 1.0f, 1.0f, 1.0f };
	skinModel.UpdateWorldMatrix(trans, rotation, scale);
}

void HUD::Render()
{
	skinModel.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
	//sprite.Draw();
}

