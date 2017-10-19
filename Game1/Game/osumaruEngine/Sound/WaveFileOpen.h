#pragma once
class WaveFileOpen
{
public:
	WaveFileOpen();

	~WaveFileOpen();

	void Open(char* fileName);

	WAVEFORMATEX* GetFormat()
	{
		return m_format;
	}

	DWORD GetSize()
	{
		return m_size;
	}

	char* GetSoundData()
	{
		return m_readMemory;
	}

private:

	void Read();

private:
	HMMIO			m_hmmio;
	MMCKINFO		m_riffChunk;
	MMCKINFO		m_dataChunk;
	DWORD			m_size;
	char*			m_readMemory;
	WAVEFORMATEX*	m_format;
};