#pragma once
#include "MapChip.h"

//�w�i�I�u�W�F�N�g

class StaticMapObject : public MapChip
{
public:
	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)override;

	//�������֐�
	void Start()override;

private:
	RigidBody		m_rigidBody;		//����
	MeshCollider	m_meshCollider;		//�R���C�_�[
};
