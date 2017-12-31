#pragma once
struct GhostData
{
	D3DXVECTOR3 position;
	D3DXQUATERNION rotation;
	float animationUpdateTime;
	int currentAnimationNum;
};