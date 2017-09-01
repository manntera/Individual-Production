#pragma once

class HUD  : public GameObject
{
public:
	void Init(LPDIRECT3DDEVICE9 pDevice);

	void Update() override;

	void Render() override;
private:
	//Sprite			sprite;
	SkinModel		skinModel;
	SkinModelData	skinModelData;
	Light			light;

	D3DXQUATERNION	rotation;
};
