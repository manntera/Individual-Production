#pragma once

//�G�t�F�N�g��ǂݍ���ŕێ�����N���X

class EffectManager
{
public:
	//�R���X�g���N�^
	EffectManager();

	//�f�X�g���N�^
	~EffectManager();

	/*
	�G�t�F�N�g�̃��[�h
	�ǂݍ��ݍς݂̃G�t�F�N�g�̓��[�h�����Ɋ����̃G�t�F�N�g���Ԃ��Ă���
	filePath		�ǂݍ��ރt�@�C���̃p�X�B
	return			�ǂݍ��񂾃G�t�F�N�g
	*/
	LPD3DXEFFECT LoadEffect(char* filePath);

	//�n�b�V���l�𕶎��񂩂�int�̒l�ō��֐�
	int MakeHash(char* string);

	//�����[�X
	void Release();
private:
	std::map<int, LPD3DXEFFECT> m_effectDictionary;	//�G�t�F�N�g���t�@�C���p�X�̃n�b�V���l���L�[�Ɏ��B
};