#pragma once

class Test : public GameObject
{
public:

	void Init(D3DXVECTOR3 position);

	void Update()override;

	void Render()override;
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