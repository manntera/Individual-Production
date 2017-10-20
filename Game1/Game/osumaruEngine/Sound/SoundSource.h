#pragma once
#include "WaveFileOpen.h"

class SoundSource : public GameObject
{
public:
	//�R���X�g���N�^
	SoundSource();

	//�f�X�g���N�^
	~SoundSource();

	/*
	������
	filePath		�ǂݍ��݂���Wave�t�@�C���̃p�X
	*/
	void Init(char* filePath);

	//�X�V
	void Update()override;

	/*
	�Đ�
	isLoop		���[�v�����邩�Htrue�Ȃ烋�[�v�Afalse�Ȃ烋�[�v���Ȃ�
	*/
	void Play(bool isLoop);

private:
	IXAudio2SourceVoice*	m_sourceVoice;		//�\�[�X�{�C�X
	WaveFileOpen			m_waveFile;			//WAVE�t�@�C���̃f�[�^
	bool					m_isLoop;			//���[�v�t���O
	bool					m_isPlaying;		//�Đ������H
};