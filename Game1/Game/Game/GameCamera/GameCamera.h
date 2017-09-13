#pragma once
class GameCamera : public GameObject
{
public:
	GameCamera();
	
	~GameCamera();

	void Init();

	void Update()override;

	Camera& GetCamera()
	{
		return camera;
	}

private:
	D3DXQUATERNION	rotation;
	Camera			camera;

};