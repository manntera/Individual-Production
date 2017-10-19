#pragma once

class SoundEngine : Uncopyable
{
public:

	SoundEngine();

	~SoundEngine();

	void Init();

	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format);

private:
	IXAudio2*				m_xAudio;
	IXAudio2MasteringVoice* m_masteringVoice;
};
