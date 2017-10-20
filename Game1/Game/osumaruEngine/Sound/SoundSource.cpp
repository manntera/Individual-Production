#include "engineStdafx.h"
#include "SoundSource.h"
#include "../Engine.h"

SoundSource::SoundSource()
{
	m_sourceVoice = nullptr;
	m_isLoop = false;
	m_isPlaying = false;
}

SoundSource::~SoundSource()
{
	if (m_sourceVoice != nullptr)
	{
		m_sourceVoice->DestroyVoice();
	}
}

void SoundSource::Init(char* filePath)
{
	//WAVE�t�@�C����ǂݍ���
	m_waveFile.Open(filePath);
	//�\�[�X�{�C�X���쐬
	m_sourceVoice = GetSoundEngine().CreateSouceVoice(m_waveFile.GetFormat());
}

void SoundSource::Update()
{
	//�Đ����ĂȂ���΍X�V�s�v
	if (!m_isPlaying)
	{
		return;
	}
	XAUDIO2_VOICE_STATE state;
	m_sourceVoice->GetState(&state);
	if (state.BuffersQueued <= 0)
	{
		m_isPlaying = false;
		if (m_isLoop)
		{
			Play(m_isLoop);
		}
		else
		{
			Delete(this);
		}
	}
}

void SoundSource::Play(bool isLoop)
{
	m_isLoop = isLoop;
	if (m_isPlaying)
	{
		m_sourceVoice->Start();
	}
	else
	{
		//�o�b�t�@���N���A
		m_sourceVoice->FlushSourceBuffers();
		//�Đ��J�n�̃t���O
		m_sourceVoice->Start(0);
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = (BYTE*)m_waveFile.GetSoundData();
		buffer.AudioBytes = m_waveFile.GetSize();
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		//�\�[�X�{�C�X�ɃI�[�f�B�o�b�t�@�𑗂�Đ��J�n
		if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer)))
		{
			throw;
		}
		m_isPlaying = true;
	}
}