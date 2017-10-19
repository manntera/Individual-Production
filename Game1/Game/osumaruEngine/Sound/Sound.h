#pragma once

class Sound : Uncopyable
{
public:
	void Init(char* filePath);

	void Play();

	void Update();

	void Submit();
private:
	MMIOINFO mmioInfo;
	HMMIO hMmio;
	MMCKINFO riffChunk;
	MMCKINFO formatChunk;
	MMCKINFO dataChunk;
	DWORD m_size;
	WAVEFORMATEX* formatex;
	char* pData;
	IXAudio2*	m_xAudio2;
	IXAudio2SourceVoice* m_sourceVoice;
	IXAudio2MasteringVoice* m_masteringVoice;
	bool isPlaying = false;
};