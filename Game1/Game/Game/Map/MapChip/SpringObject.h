#pragma once
#include "MapChip.h"
//�o�l�I�u�W�F�N�g

class SpringObject : public MapChip
{
public:
	//�R���X�g���N�^
	SpringObject();

	//�f�X�g���N�^
	~SpringObject();

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
	RigidBody		m_rigidBody;		//����
	BoxCollider		m_boxCollider;		//�R���C�_�[
	Animation		m_anim;				//�A�j���[�V����
};