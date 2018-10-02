#pragma once
#include "MapChip.h"
//������I�u�W�F�N�g

class FallObject2 : public MapChip
{
public:
	//�R���X�g���N�^
	FallObject2();

	//�f�X�g���N�^
	~FallObject2();

	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim = nullptr)override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:

	//�T�E���h������
	void SoundDelete();

private:
	bool				m_isFall;			//�����n�߂���
	RigidBody			m_rigidBody;		//����
	BoxCollider			m_boxCollider;		//�R���C�_�[
	float				m_timer;			//������܂ł̎���
	float				m_animationTimer;	//�h���A�j���[�V���������鎞��
	D3DXVECTOR3			m_animationMove;	//�h���A�j���[�V���������邽�߂̈ړ����x
	SoundSource*		m_pSound;			//�T�E���h
	float				m_soundVolume;		//�T�E���h�̃{�����[��
};