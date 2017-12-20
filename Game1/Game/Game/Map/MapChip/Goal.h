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
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr)override;

	//�X�V�֐�
	void Update()override;
private:
};