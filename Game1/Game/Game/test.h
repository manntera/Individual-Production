#pragma once

class Test : public GameObject
{
public:

	void Init();

	void Update()override;

	void Render(int num);
private:
	SkinModel		skinModel;
	SkinModelData	skinModelData;
	Light			light;
	RigidBody		rigidBody;
	MeshCollider	meshCollider;
	BoxCollider		boxCollider;
	D3DXVECTOR3 trans;
	D3DXQUATERNION rotation;
};