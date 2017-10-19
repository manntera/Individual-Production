#include "engineStdafx.h"
#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
	m_xAudio = nullptr;
	m_masteringVoice = nullptr;

}

SoundEngine::~SoundEngine()
{
	if (m_masteringVoice != nullptr)
	{
		m_masteringVoice->DestroyVoice();
	}
	if (m_xAudio != nullptr)
	{
		m_xAudio->Release();
	}
}

void SoundEngine::Init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&m_xAudio, 0)))
	{
		throw;
	}
	if (FAILED(m_xAudio->CreateMasteringVoice(&m_masteringVoice)))
	{
		throw;
	}

}

IXAudio2SourceVoice* SoundEngine::CreateSouceVoice(WAVEFORMATEX* format)
{
	IXAudio2SourceVoice* sourceVoice;
	m_xAudio->CreateSourceVoice(&sourceVoice, format);
	return sourceVoice;
}