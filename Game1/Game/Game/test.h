#pragma once

class Test : public GameObject
{
public:

	void Init();

	void Update()override;

	void Render();
private:
	SkinModel		skinModel;
	SkinModelData	skinModelData;
	Light			light;
	RigidBody		rigidBody;
	MeshCollider	meshCollider;
};