#pragma once
#include "MapChip.h"
//�X�e�[�W�M�~�b�N�̓������~�߂邱�Ƃ��ł���A�C�e��

class StopTimeItem : public MapChip
{
public:
	//�R���X�g���N�^
	StopTimeItem();


	//�X�V�֐�
	void Update()override;

	void Draw()override;

private:
	bool	m_isDead;
	float	m_revivalTime;
};