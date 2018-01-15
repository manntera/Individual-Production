#pragma once
//���t���[���L�^����S�[�X�g�𓮂������߂̃f�[�^
struct GhostData	
{
	D3DXVECTOR3 position;			//���W
	D3DXQUATERNION rotation;		//��]
	float animationUpdateTime;		//�A�j���[�V�����̍X�V����
	int currentAnimationNum;		//�Đ����Ă���A�j���[�V�����̔ԍ�
};

//�S�[�X�g�f�[�^�̃��X�g
struct GhostDataList
{
	std::list<GhostData> ghostData;	//�f�[�^�̃��X�g
	float time;						//�X�^�[�g����S�[���܂ł̃^�C��
};