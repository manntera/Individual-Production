#pragma once
#include "MapChip.h"
//�S�[���N���X�A�v���C���[��������ƃQ�[���N���A�ɂȂ�

class Goal : public MapChip
{
public:
	//�R���X�g���N�^
	Goal();

	//�f�X�g���N�^
	~Goal();

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
};