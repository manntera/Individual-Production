#pragma once
class Camera
{
public:
	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//�A�X�y�N�g���ݒ�
	void SetAspect(float _aspect);

	//�A�X�y�N�g����擾
	float GetAspect();

	//�t�@�[��ݒ�
	void SetFar(float _far);

	//�t�@�[���擾
	float GetFar();

	//�j�A��ݒ�
	void SetNear(float _near);

	//�j�A���擾
	float GetNear();

	//���_��ݒ�
	void SetTarget(D3DXVECTOR3 target);

	//���_���擾
	D3DXVECTOR3 GetTarget();

	//���W��ݒ�
	void SetPosition(D3DXVECTOR3 position);

	//���W���擾
	D3DXVECTOR3 GetPosition();

	//�J�����̏������ݒ�
	void SetUp(D3DXVECTOR3 up);

	//�J�����̏�������擾
	D3DXVECTOR3 GetUp();

	//�r���[�s��̐ݒ�B
	void SetViewMatrix(D3DXMATRIX view);

	//�r���[�s��̎擾
	D3DXMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s��̐ݒ�B
	void SetProjectionMatrix(D3DXMATRIX projection);

	//�v���W�F�N�V�����s��̐ݒ�B
	D3DXMATRIX GetProjectionMatrix();

	//������
	void Init();

	//�X�V����
	void Update();

private:
	D3DXMATRIX			m_viewMatrix;			//�r���[�s��B�J�����s��Ƃ������B
	D3DXMATRIX			m_projectionMatrix;		//�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����B
	D3DXVECTOR3			m_position;				//�J�����̎��_�B
	D3DXVECTOR3			m_target;				//�J�����̒����_
	D3DXVECTOR3			m_up;					//�J�����̏����
	float				m_Far;					//������
	float				m_Near;					//�ߕ���
	float				m_Aspect;				//�A�X�y�N�g��
};