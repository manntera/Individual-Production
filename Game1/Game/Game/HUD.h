#pragma once

class HUD  : public GameObject
{
public:
	void Init();

	void Update() override;

	void Render() override;
private:
	SkinModel		skinModel;
	SkinModelData	skinModelData;
	Light			light;
	D3DXQUATERNION	rotation;
	D3DXVECTOR3		trans;
	D3DXVECTOR3		scale;
	CapsuleCollider	capsuleCollider;
	RigidBody		rigidBody;
	Sprite			sprite;
};
