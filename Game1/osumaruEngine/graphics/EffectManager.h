#pragma once
#include "../common.h"

class EffectManager
{
public:

	EffectManager();

	~EffectManager();

	/*
	�G�t�F�N�g�̃��[�h
	�ǂݍ��ݍς݂̃G�t�F�N�g�̓��[�h�����Ɋ����̃G�t�F�N�g���Ԃ��Ă���
	*/
	ID3DXEffect* LoadEffect(const char* filePath);

	void Release();
private:
	std::map<int, ID3DXEffect*> effectDictionary;
};