#pragma once

//�G�t�F�N�g��ǂݍ���ŕێ�����N���X

class EffectManager
{
public:
	//�R���X�g���N�^
	EffectManager();

	~EffectManager();

	/*
	�G�t�F�N�g�̃��[�h
	�ǂݍ��ݍς݂̃G�t�F�N�g�̓��[�h�����Ɋ����̃G�t�F�N�g���Ԃ��Ă���
	filePath		�ǂݍ��ރt�@�C���̃p�X�B
	*/
	LPD3DXEFFECT LoadEffect(const char* filePath);

	//�n�b�V���l�𕶎��񂩂�int�̒l�ō��֐�
	int MakeHash(const char* string);

	//�����[�X
	void Release();
private:
	std::map<int, LPD3DXEFFECT> effectDictionary;	//�G�t�F�N�g���t�@�C���p�X�̃n�b�V���l���L�[�Ɏ��B
};