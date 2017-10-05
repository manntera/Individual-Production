#pragma once
#include "MapChip.h"

class SpringObject : public MapChip
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
	RigidBody		m_rigidBody;		//����
	MeshCollider	m_meshCollider;		//�R���C�_�[
};