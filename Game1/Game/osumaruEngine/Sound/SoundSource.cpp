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
	//WAVEファイルを読み込み
	m_waveFile.Open(filePath);
	//ソースボイスを作成
	m_sourceVoice = GetSoundEngine().CreateSouceVoice(m_waveFile.GetFormat());
}

void SoundSource::Update()
{
	//再生してなければ更新不要
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
		//バッファをクリア
		m_sourceVoice->FlushSourceBuffers();
		//再生開始のフラグ
		m_sourceVoice->Start(0);
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = (BYTE*)m_waveFile.GetSoundData();
		buffer.AudioBytes = m_waveFile.GetSize();
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		//ソースボイスにオーディバッファを送り再生開始
		if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer)))
		{
			throw;
		}
		m_isPlaying = true;
	}
}