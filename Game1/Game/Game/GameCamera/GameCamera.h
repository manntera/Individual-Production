#pragma once
//�Q�[���J�����N���X

class GameCamera : public GameObject
{
public:
	//�R���X�g���N�^
	GameCamera();
	
	//�f�X�g���N�^
	~GameCamera();

	//�������֐�
	void Init();

	//�X�V�֐�
	void Update()override;

	//�J�����̎擾
	Camera& GetCamera()
	{
		return camera;
	}

private:
	D3DXQUATERNION	rotation;		//�J�����̉�]
	Camera			camera;			//�J����

};