#include "engineStdafx.h"
#include "SoundSource.h"
#include "../Engine.h"

SoundSource::SoundSource()
{
	m_sourceVoice = nullptr;
	m_isLoop = false;
	m_isPlaying = false;
	memset(m_coefficients, 0, sizeof(m_coefficients));
	memset(m_emitterAzimuths, 0, sizeof(m_emitterAzimuths));
	m_position = { 0.0f, 0.0f, 0.0f };
	m_is3DSound = false;
}

SoundSource::~SoundSource()
{
	if (m_sourceVoice != nullptr)
	{
		m_sourceVoice->DestroyVoice();
	}
	if (m_is3DSound)
	{
		GetSoundEngine().Delete3dSound(this);
	}
}

void SoundSource::Init(char* filePath, bool is3DSound)
{
	//WAVEファイルを読み込み
	m_waveFile.Open(filePath);
	//ソースボイスを作成
	m_sourceVoice = GetSoundEngine().CreateSouceVoice(m_waveFile.GetFormat(), is3DSound);

	m_dspSettings.pMatrixCoefficients = m_coefficients;
	m_dspSettings.pDelayTimes = nullptr;
	m_dspSettings.SrcChannelCount = INPUTCHANNELS;
	m_dspSettings.DstChannelCount = GetSoundEngine().GetChannelNum();
	m_dspSettings.DopplerFactor = 1.0f;
	m_dspSettings.LPFDirectCoefficient = 0.82142854f;
	m_dspSettings.LPFReverbCoefficient = 0.75f;
	m_dspSettings.ReverbLevel = 0.69114286f;
	m_dspSettings.EmitterToListenerAngle = 0.0f;
	m_dspSettings.EmitterToListenerDistance = 10.0f;
	m_dspSettings.EmitterVelocityComponent = 0.0f;
	m_dspSettings.ListenerVelocityComponent = 0.0f;
	m_is3DSound = is3DSound;
	if (m_is3DSound)
	{
		GetSoundEngine().Add3dSound(this);
	}
}

void SoundSource::Stop()
{
	m_sourceVoice->Stop();
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