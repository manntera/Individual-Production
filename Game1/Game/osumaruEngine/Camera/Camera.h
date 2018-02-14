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
	float GetAspect() const;

	//�t�@�[��ݒ�
	void SetFar(float _far);

	//�t�@�[���擾
	float GetFar() const;

	//�j�A��ݒ�
	void SetNear(float _near);

	//�j�A���擾
	float GetNear() const;

	//���_��ݒ�
	void SetTarget(const D3DXVECTOR3& target);

	//���_���擾
	const D3DXVECTOR3& GetTarget() const;

	//���W��ݒ�
	void SetPosition(const D3DXVECTOR3& position);

	//���W���擾
	const D3DXVECTOR3& GetPosition() const;

	//�J�����̏������ݒ�
	void SetUp(const D3DXVECTOR3& up);

	//�J�����̏�������擾
	const D3DXVECTOR3& GetUp() const;

	//�r���[�s��̐ݒ�B
	void SetViewMatrix(const D3DXMATRIX& view);

	//�r���[�s��̎擾
	const D3DXMATRIX& GetViewMatrix() const;

	//�v���W�F�N�V�����s��̐ݒ�B
	void SetProjectionMatrix(const D3DXMATRIX& projection);

	//�v���W�F�N�V�����s��̎擾�B
	const D3DXMATRIX& GetProjectionMatrix() const;

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