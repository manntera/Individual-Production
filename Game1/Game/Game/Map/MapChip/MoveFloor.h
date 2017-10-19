#pragma once
#include "MapChip.h"
const float g_moveFloorSpeed = 0.2f;

class MoveFloor : public MapChip
{
public:
	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr)override;

	void Update()override;
private:
	float			m_timer;
	D3DXVECTOR3		m_moveSpeed;
	RigidBody		m_rigidBody;		//����
	BoxCollider		m_boxCollider;		//�R���C�_�[
	bool			m_isChild;			
};