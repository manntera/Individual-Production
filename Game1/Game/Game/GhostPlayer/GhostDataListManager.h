#pragma once
#include "GhostCommon.h"
//�S�[�X�g�f�[�^���L�^����N���X

class GhostDataListManager : public GameObject
{
private:
	//�R���X�g���N�^
	GhostDataListManager();

	//�f�X�g���N�^
	~GhostDataListManager();
public:
	/*
	�v���J�n����֐�
	position	�v���C���[�̍��W�̃A�h���X
	rotation	�v���C���[�̉�]�̃A�h���X
	animation	�v���C���[�̃A�j���[�V����
	*/
	void Start(D3DXVECTOR3* position, D3DXQUATERNION* rotation, Animation* animation);

	/*
	�v���I������֐�
	time		�X�e�[�W���N���A�����^�C��
	isClear		�N���A�������H
	*/
	void Finish(float time, bool isClear);

	//�X�V�֐�
	void Update()override;

	//�S�[�X�g�f�[�^���擾
	std::list<GhostData>& GetGhostData()
	{
		return m_ghostData[m_stageNum].ghostData;
	}

	static GhostDataListManager& GetInstance() 
	{
		static GhostDataListManager ghostDataListManager;
		return ghostDataListManager;
	}
private:
	D3DXVECTOR3*				m_pPosition;		//�v���C���[�̍��W
	D3DXQUATERNION*				m_pRotation;		//�v���C���[�̉�]
	Animation*					m_pAnimation;		//�v���C���[�̃A�j���[�V����
	std::vector<GhostDataList>	m_ghostData;		//�X�e�[�W���̃S�[�X�g�f�[�^���X�g
	std::list<GhostData>		m_substitute;		//�S�[�X�g�f�[�^���X�g
	int							m_stageNum;			//�X�e�[�W�̔ԍ�
	bool						m_isActive;			//�A�N�e�B�u���H
};


static GhostDataListManager& GetGhostDataListManager()
{
	return GhostDataListManager::GetInstance();
}