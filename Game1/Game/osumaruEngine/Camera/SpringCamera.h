#pragma once
#include "Camera.h"
//�o�l�J����

class SpringCamera
{
public:
	//�R���X�g���N�^
	SpringCamera();

	//�f�X�g���N�^
	~SpringCamera();

	/*
	������
	*/
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);

	
	//�ڕW�ƂȂ钍���_��ݒ�B
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}

	//�����_��ݒ�
	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetTarget(target);
	}

	
	//�ڕW�ƂȂ鎋�_��ݒ�
	void SetTarPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
	}

	//���_��ݒ�
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_camera.SetPosition(position);
	}

	//�����ʂ��擾
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}

	//�����_���擾
	const D3DXVECTOR3& GetTarget() const
	{
		return m_camera.GetTarget();
	}

	//���_���擾
	const D3DXVECTOR3& GetPosition() const
	{
		return m_camera.GetPosition();
	}

	//�X�V�֐�
	void Update();

	//�J�������擾
	const Camera* GetCamera() const
	{
		return &m_camera;
	}

	/*
	�o�l�̌�������ݒ�
	dampingRate		�������A���̒l���傫���قǃJ�������x��Ă��Ă���
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}

	//�ڕW�ƂȂ钍���_���擾
	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}

	//�ڕW�ƂȂ鎋�_���擾
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}

	//�o�l�J�����p�̃p�����[�^���N���A
	void ClearSpringParame()
	{
		m_target = {0.0f, 0.0f, 0.0f};
		m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	/*
	�o�l�J�����̍X�V
	�o�l�J�����̂ݍX�V�������Ƃ��Ɏg��
	*/
	void UpdateSpringCamera();

	/*
	�J�����̍X�V
	�J�����̂ݍX�V�������Ƃ��Ɏg��
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}
private:

	D3DXVECTOR3 CalcSpringVector(const D3DXVECTOR3& positionNow, const D3DXVECTOR3& positionTarget, D3DXVECTOR3& moveSpeed, float maxMoveSpeed, float dampingRate);

	float CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed);
private:
	Camera		m_camera;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_targetMoveSpeed;
	D3DXVECTOR3 m_positionMoveSpeed;
	float		m_maxMoveSpeed;
	float		m_targetDampingRate;
	float		m_dampingRate;
	float		m_dampingRateVel;
	const float m_dampingK;
};