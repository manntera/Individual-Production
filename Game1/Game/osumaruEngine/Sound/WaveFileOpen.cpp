#include "engineStdafx.h"
#include "WaveFileOpen.h"

WaveFileOpen::WaveFileOpen()
{
	m_format = nullptr;
	m_readMemory = nullptr;
	m_size = 0;
}

WaveFileOpen::~WaveFileOpen()
{
	if (m_format != nullptr)
	{
		delete[] m_format;
	}
	mmioClose(m_hmmio, 0);
}


void WaveFileOpen::Open(char* filePath)
{
	//WAVEファイルを開く
	m_hmmio = mmioOpen(filePath, NULL, MMIO_ALLOCBUF | MMIO_READ);

	m_riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (0 != mmioDescend(m_hmmio, &m_riffChunk, NULL, 0))
	{
		throw;
	}
	MMCKINFO formatChunk;
	memset(&formatChunk, 0, sizeof(formatChunk));
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(m_hmmio, &formatChunk, &m_riffChunk, MMIO_FINDCHUNK))
	{
		throw;
	}
	PCMWAVEFORMAT pcmFormat;
	if (mmioRead(m_hmmio, (HPSTR)&pcmFormat, sizeof(pcmFormat)) != sizeof(pcmFormat))
	{
		throw;
	}
	m_format = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(m_format, &pcmFormat, sizeof(pcmFormat));
	if (pcmFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		m_format = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		memcpy(m_format, &pcmFormat, sizeof(pcmFormat));
		m_format->cbSize = 0;
	}
	else
	{
		WORD cbExtraByts = 0L;
		if (mmioRead(m_hmmio, (CHAR*)&cbExtraByts, sizeof(WORD)) != sizeof(WORD))
		{
			throw;
		}
		m_format = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraByts];
		memcpy(m_format, &pcmFormat, sizeof(pcmFormat));
		m_format->cbSize = cbExtraByts;
		if (mmioRead(m_hmmio, (CHAR*)(((BYTE*)&(m_format->cbSize)) + sizeof(WORD)), cbExtraByts) != cbExtraByts)
		{
			throw;
		}
	}
	if (0 != mmioAscend(m_hmmio, &formatChunk, 0))
	{
		throw;
	}
	if (-1 == mmioSeek(m_hmmio, m_riffChunk.dwDataOffset + sizeof(FOURCC), SEEK_SET))
	{
		throw;
	}
	m_dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if (0 != mmioDescend(m_hmmio, &m_dataChunk, &m_riffChunk, MMIO_FINDCHUNK))
	{
		throw;
	}
	Read();
}

void WaveFileOpen::Read()
{
	m_size = m_dataChunk.cksize;
	//データ読み込み用のバッファを確保
	m_readMemory.reset(new char[m_size]);

	MMIOINFO  mmioInfo;
	if (0 != mmioGetInfo(m_hmmio, &mmioInfo, 0))
	{
		throw;
	}
	UINT cbDataIn = m_size;

	//データを読み込み
	for (DWORD cT = 0; cT < cbDataIn; cT++)
	{
		if (mmioInfo.pchNext == mmioInfo.pchEndRead)
		{
			if (0 != mmioAdvance(m_hmmio, &mmioInfo, MMIO_READ))
			{
				throw;
			}
			if (mmioInfo.pchNext == mmioInfo.pchEndRead)
			{
				throw;
			}
		}
		*((BYTE*)m_readMemory.get() + cT) = *((BYTE*)mmioInfo.pchNext);
		mmioInfo.pchNext++;
	}
}