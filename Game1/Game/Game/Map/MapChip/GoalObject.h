#pragma once
#include "MapChip.h"
//�S�[���������I�u�W�F�N�g

class GoalObject : public MapChip
{
public:
	//�R���X�g���N�^
	GoalObject();

	//�f�X�g���N�^
	~GoalObject();

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
private:
	D3DXQUATERNION m_multi;	//���t���[����]������̂Ɏg���N�H�[�^�[�j�I��
};