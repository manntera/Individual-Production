#include "stdafx.h"
#include "HUD.h"

void HUD::Init(LPDIRECT3DDEVICE9 pDevice)
{
	sprite.Init("../Game/Assets/sprite/Texture.jpg");

}

void HUD::Update()
{
	D3DXVECTOR2 position = sprite.GetPosition();
	if (GetAsyncKeyState(VK_LEFT))
	{
		position.x -= 10.0f;
 	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		position.x += 10.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVECTOR2 size = sprite.GetSize();
		size *= 0.99f;
		sprite.SetSize(size);
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		D3DXVECTOR2 size = sprite.GetSize();
		size /= 0.99f;
		sprite.SetSize(size);
	}
	sprite.SetPosition(position);
}

void HUD::Render()
{
	sprite.Draw();
}

