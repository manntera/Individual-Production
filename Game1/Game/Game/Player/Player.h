#pragma once
class Player : public GameObject
{
public:
	void Init();

	void Update() override;

	void Render() override;

	D3DXVECTOR3 GetPosition()
	{
		return trans;
	}
private:
	SkinModel		skinModel;
	SkinModelData	skinModelData;
	Light			light;
	D3DXQUATERNION	rotation;
	D3DXVECTOR3		trans;
	D3DXVECTOR3		scale;
	Animation		anim;
	CharacterController characterController;
};