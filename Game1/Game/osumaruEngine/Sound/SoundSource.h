#pragma once
#include "WaveFileOpen.h"

class SoundSource : public GameObject
{
public:
	SoundSource();

	~SoundSource();

	void Init(char* filePath);

	void Start()override;

	void Update()override;

	void Play(bool isLoop);

private:
	IXAudio2SourceVoice*	m_sourceVoice;
	WaveFileOpen			m_waveFile;
	bool					m_isLoop;
	bool					m_isPlaying;
};