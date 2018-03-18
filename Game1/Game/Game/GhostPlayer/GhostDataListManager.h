#pragma once
#include "GhostCommon.h"
//�S�[�X�g�f�[�^���L�^���Ǘ�����N���X

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
	void Start(const D3DXVECTOR3* position, const D3DXQUATERNION* rotation, const Animation* animation);

	/*
	�v���I������֐�
	time		�X�e�[�W���N���A�����^�C��
	isClear		�N���A�������H
	*/
	void Finish(float time, bool isClear);

	//�X�V�֐�
	void Update()override;

	//�S�[�X�g�f�[�^���擾
	const std::list<GhostData>& GetGhostData() const
	{
		return m_ghostData[m_stageNum].ghostData;
	}

	//���g�̃C���X�^���X���擾
	static GhostDataListManager& GetInstance() 
	{
		static GhostDataListManager ghostDataListManager;
		return ghostDataListManager;
	}

	//�S�[�X�g�f�[�^�̓ǂݍ���
	void GhostDataRead();

	//�S�[�X�g�f�[�^�̃Z�[�u
	void GhostDataSave();


	//�A�N�e�B�u���̃t���O��ݒ肷��B
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}
private:
	const D3DXVECTOR3*			m_pPosition;		//�v���C���[�̍��W
	const D3DXQUATERNION*		m_pRotation;		//�v���C���[�̉�]
	const Animation*			m_pAnimation;		//�v���C���[�̃A�j���[�V����
	std::vector<GhostDataList>	m_ghostData;		//�X�e�[�W���̃S�[�X�g�f�[�^���X�g
	std::list<GhostData>		m_substitute;		//�S�[�X�g�f�[�^���X�g
	int							m_stageNum;			//�X�e�[�W�̔ԍ�
	bool						m_isActive;			//�A�N�e�B�u���H
};


//�S�[�X�g�f�[�^���X�g�}�l�[�W���[���擾�B
static GhostDataListManager& GetGhostDataListManager()
{
	return GhostDataListManager::GetInstance();
}