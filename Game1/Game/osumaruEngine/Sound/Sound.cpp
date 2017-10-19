#include "engineStdafx.h"
#include "Sound.h"

void Sound::Init(char* filePath)
{
	pData = nullptr;
	m_sourceVoice = nullptr;
	m_masteringVoice = nullptr;
	hMmio = mmioOpen(filePath, NULL, MMIO_ALLOCBUF | MMIO_READ);

	//memset(&riffChunk, 0, sizeof(riffChunk));
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (0 != mmioDescend(hMmio, &riffChunk, NULL, 0))
	{
		throw;
	}
	memset(&formatChunk, 0, sizeof(formatChunk));
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK))
	{
		throw;
	}

	PCMWAVEFORMAT pcmFormat;
	if (mmioRead(hMmio, (HPSTR)&pcmFormat, sizeof(pcmFormat)) != sizeof(pcmFormat))
	{
		throw;
	}
	if (pcmFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		formatex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		memcpy(formatex, &pcmFormat, sizeof(pcmFormat));
		formatex->cbSize = 0;
	}
	else
	{
		WORD cbExtraByts = 0L;
		if (mmioRead(hMmio, (CHAR*)&cbExtraByts, sizeof(WORD)) != sizeof(WORD))
		{
			throw;
		}
		formatex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraByts];
		memcpy(formatex, &pcmFormat, sizeof(pcmFormat));
		formatex->cbSize = cbExtraByts;
		if ( mmioRead(hMmio, (CHAR*) ( ( (BYTE*)&(formatex->cbSize) ) + sizeof(WORD) ), cbExtraByts) != cbExtraByts )
		{
			throw;
		}
	}
	if (0 != mmioAscend(hMmio, &formatChunk, 0))
	{
		throw;
	}
	if (-1 == mmioSeek(hMmio, riffChunk.dwDataOffset + sizeof(FOURCC), SEEK_SET))
	{
		throw;
	}
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if (0 != mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK))
	{
		throw;
	}
	//size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);
	//mmioClose(hMmio, 0);
	m_size = dataChunk.cksize;
	pData = new char[m_size];

	MMIOINFO  mmioInfo;
	if (0 != mmioGetInfo(hMmio, &mmioInfo, 0))
	{
		throw;
	}
	UINT cbDataIn = m_size;
	//if (dataChunk.cksize < cbDataIn)
	//{
	//	cbDataIn = dataChunk.cksize;
	//}
	//dataChunk.cksize -= cbDataIn;

	for (DWORD cT = 0; cT < cbDataIn; cT++)
	{
		if (mmioInfo.pchNext == mmioInfo.pchEndRead)
		{
			if (0 != mmioAdvance(hMmio, &mmioInfo, MMIO_READ))
			{
				throw;
			}
			if (mmioInfo.pchNext == mmioInfo.pchEndRead)
			{
				throw;
			}
		}

		*((BYTE*)pData + cT) = *((BYTE*)mmioInfo.pchNext);
		mmioInfo.pchNext++;
	}

	//if (-1 == mmioSeek(hMmio, riffChunk.dwDataOffset + sizeof(FOURCC), SEEK_SET))
	//{
	//	throw;
	//}

	//if (0 != mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK))
	//{
	//	throw;
	//}

	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&m_xAudio2, 0)))
	{
		throw;
	}
	if (FAILED(m_xAudio2->CreateMasteringVoice(&m_masteringVoice)))
	{
		throw;
	}
	if (FAILED(m_xAudio2->CreateSourceVoice(&m_sourceVoice, formatex)))
	{
		throw;
	}
	
}

void Sound::Play()
{
	m_sourceVoice->FlushSourceBuffers();
	m_sourceVoice->Start(0);
	Submit();
	isPlaying = true;
}

void Sound::Update()
{
	if (isPlaying)
	{
		XAUDIO2_VOICE_STATE state;
		m_sourceVoice->GetState(&state);
		if (state.BuffersQueued <= 0)
		{
			//Play();
			Submit();
		}
	}

}

void Sound::Submit()
{
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = (BYTE*)pData;
	buffer.AudioBytes = m_size;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer)))
	{
		throw;
	}
}