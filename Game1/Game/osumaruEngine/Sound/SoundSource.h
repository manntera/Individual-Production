#pragma once
#include "WaveFileOpen.h"
#include "SoundEngine.h"

class SoundSource : public GameObject
{
public:
	//コンストラクタ
	SoundSource();

	//デストラクタ
	~SoundSource();

	/*
	初期化
	filePath		読み込みたいWaveファイルのパス
	*/
	void Init(char* filePath, bool is3DSound = false);

	//更新
	void Update()override;

	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
	}

	/*
	再生
	isLoop		ループさせるか？trueならループ、falseならループしない
	*/
	void Play(bool isLoop);

	void Stop();

	int GetInputChannelNum()
	{
		return m_waveFile.GetFormat()->nChannels;
	}

	X3DAUDIO_DSP_SETTINGS* GetDSPSettings()
	{
		return &m_dspSettings;
	}

	FLOAT32* GetEmitterAzimuths()
	{
		return m_emitterAzimuths;
	}

	FLOAT32* GetCoefficients()
	{
		return m_coefficients;
	}

	IXAudio2SourceVoice* GetBody()
	{
		return m_sourceVoice;
	}
	D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}

	void SetVolume(float volume)
	{
		m_sourceVoice->SetVolume(volume, XAUDIO2_COMMIT_NOW);
	}
private:
	D3DXVECTOR3				m_position;
	FLOAT32					m_coefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	FLOAT32					m_emitterAzimuths[INPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS	m_dspSettings;
	IXAudio2SourceVoice*	m_sourceVoice;		//ソースボイス
	WaveFileOpen			m_waveFile;			//WAVEファイルのデータ
	bool					m_isLoop;			//ループフラグ
	bool					m_isPlaying;		//再生中か？
	bool					m_is3DSound;
};