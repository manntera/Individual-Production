#pragma once
#include "MapChip.h"

//�w�i�I�u�W�F�N�g

class StaticMapObject : public MapChip
{
public:
	//�R���X�g���N�^
	StaticMapObject();

	//�f�X�g���N�^
	~StaticMapObject();

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
