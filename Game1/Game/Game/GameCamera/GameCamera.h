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

	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�J�����̎擾
	const Camera& GetCamera() const
	{
		return m_camera;
	}

private:
	Camera				m_camera;			//�J����
	float				m_angleX;			//�J������X���������ɉ�]���Ă���p�x	
	D3DXVECTOR3			m_position;			//�v���C���[�̃��[�J���ł̏������W
	const D3DXMATRIX*	m_playerBoneMat;	//�J�����̒����_�����߂�̂Ɏg���v���C���[�̃{�[���̃��[���h�s��
	SpringCamera		m_springCamera;		//�o�l�J����
	const float			m_targetManip;		//�����_�����߂ɂ��邽�߂̕␳�l
};