#pragma once
#include "MapChip.h"

class FallObject : public MapChip
{
public:

	FallObject();

	~FallObject();
	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr)override;

	void Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;

	//�p�[�e�B�N��������
	void ParticleDelete();

private:
	bool				m_isActive;			//�A�N�e�B�u���ǂ���
	RigidBody			m_rigidBody;		//����
	BoxCollider			m_boxCollider;		//�R���C�_�[
	ParticleEmitter*	m_particle;			//�p�[�e�B�N��
};