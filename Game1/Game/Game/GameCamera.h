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
	Camera camera;

};

extern GameCamera *g_camera;