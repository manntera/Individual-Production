#pragma once
#include "MapChip.h"
//��]�I�u�W�F�N�g

class RotationObject : public MapChip
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

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw();
private:
	RigidBody		m_rigidBody;		//����
	MeshCollider	m_meshCollider;		//�R���C�_�[
	bool			m_isChild;			//�q�������邩�ǂ���
	D3DXQUATERNION	m_multi;			//��]��
};