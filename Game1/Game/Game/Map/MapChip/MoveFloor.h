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
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)override;

	void Update()override;
private:
	float			m_timer;
	D3DXVECTOR3		m_moveSpeed;
	RigidBody		m_rigidBody;		//����
	MeshCollider	m_meshCollider;		//�R���C�_�[
};