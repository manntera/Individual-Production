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

	//�X�V�֐�
	void Update()override;

private:
};