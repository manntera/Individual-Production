#pragma once

class SkinModelData;
class Animation;
//�X�L�����f���f�[�^���\�[�X

class SkinModelDataResource : Uncopyable
{
public:
	//�R���X�g���N�^
	SkinModelDataResource();

	//�f�X�g���N�^
	~SkinModelDataResource();

	/*
	���f���f�[�^�����[�h
	modelData	�ǂݍ��񂾃��f�����������
	anim		�A�j���[�V����
	fileName	���f���̃t�@�C���p�X
	*/
	void Load(SkinModelData* modelData, Animation* anim,  char* fileName);

private:
	std::map<int, SkinModelData*>	m_modelDatas;	//���f���f�[�^�̃��X�g
};