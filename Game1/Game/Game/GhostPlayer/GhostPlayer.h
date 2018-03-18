#pragma once
#include "GhostCommon.h"
//�S�[�X�g�f�[�^���Đ�����N���X

class GhostPlayer : public GameObject
{
public:
	//�R���X�g���N�^
	GhostPlayer();

	//�f�X�g���N�^
	~GhostPlayer();

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;

	//�A�N�e�B�u���̃t���O��ݒ肵�܂��B
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	SkinModelData							m_modelData;			//�X�L�����f���f�[�^
	SkinModel								m_model;				//�X�L�����f��
	Animation								m_animation;			//�A�j���[�V����
	std::list<GhostData>::const_iterator	m_ghostData;			//�S�[�X�g�f�[�^�̃C�e���[�^�[
	int										m_currentAnimationNum;	//���ݍĐ����̃A�j���[�V�����̔ԍ�
	Light									m_light;				//���f���̃��C�g
	bool									m_isGoal;				//�S�[���������H
	bool									m_isActive;				//�A�N�e�B�u���H
};