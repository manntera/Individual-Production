#pragma once
#include "MapChip.h"
//������I�u�W�F�N�g

class FallObject3 : public MapChip
{
public:
	//�R���X�g���N�^
	FallObject3();

	//�f�X�g���N�^
	~FallObject3();

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
	//�p�[�e�B�N��������
	void ParticleDelete();

	//�T�E���h������
	void SoundDelete();

	//�ď�����
	void Reset();

	//�p�[�e�B�N�����o��
	void ParticleEmitt();
private:
	bool				m_isFall;			//�����n�߂���
	RigidBody			m_rigidBody;		//����
	BoxCollider			m_boxCollider;		//�R���C�_�[
	ParticleEmitter*	m_particle;			//�p�[�e�B�N��
	float				m_timer;			//������܂ł̎���
	float				m_animationTimer;	//�h���A�j���[�V���������鎞��	
	D3DXVECTOR3			m_animationMove;	//�h���A�j���[�V���������邽�߂̈ړ����x
	SoundSource*		m_pSound;			//�T�E���h
	float				m_soundVolume;		//�T�E���h�̃{�����[��
	float				m_revivalTime;		//����ł��畜������܂ł̎���
	bool				m_isDead;			//����ł邩�H
	D3DXVECTOR3			m_initPos;			//�������p�̍��W
};