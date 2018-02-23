#include "engineStdafx.h"
#include "SoundEngine.h"
#include "SoundSource.h"
#include "../Engine.h"

SoundEngine::SoundEngine()
{
	m_xAudio = nullptr;
	m_masteringVoice = nullptr;
	m_channelNum = 0;
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
	if (FAILED(hr = m_xAudio->CreateMasteringVoice(&m_masteringVoice)))
	{
		throw;
	}

	XAUDIO2_DEVICE_DETAILS details;
	m_xAudio->GetDeviceDetails(0, &details);
	m_channelNum = details.OutputFormat.Format.nChannels;
	X3DAudioInitialize(details.OutputFormat.dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, m_3dAudioHandle);

	m_3dListener.OrientTop = { 0.0f, 1.0f, 0.0f };
	m_3dListener.OrientFront = { 0.0f, 0.0f, 1.0f };
	m_3dListener.Position = { 0.0f, 0.0f, 0.0f };
	m_3dListener.pCone = NULL;
}

void SoundEngine::Update()
{
	for (SoundSource* sound : m_3dSound)
	{
		X3DAUDIO_EMITTER emitter;
		emitter.pCone = NULL;

		emitter.Position.x = sound->GetPosition().x;
		emitter.Position.y = sound->GetPosition().y;
		emitter.Position.z = sound->GetPosition().z;
		emitter.OrientFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		emitter.OrientTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		emitter.ChannelCount = INPUTCHANNELS;
		emitter.ChannelRadius = 1.0f;
		emitter.pChannelAzimuths = sound->GetEmitterAzimuths();

		// Use of Inner radius allows for smoother transitions as
		// a sound travels directly through, above, or below the listener.
		// It also may be used to give elevation cues.
		emitter.InnerRadius = 0.0f;
		emitter.InnerRadiusAngle = 0.0f;

		emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
		emitter.pLFECurve = NULL;
		emitter.pLPFDirectCurve = NULL; // use default curve
		emitter.pLPFReverbCurve = NULL; // use default curve
		emitter.pReverbCurve = NULL;
		emitter.CurveDistanceScaler = 30.0f;
		emitter.DopplerScaler = 1.0f;
		X3DAUDIO_DSP_SETTINGS* dsp = sound->GetDSPSettings();
		DWORD dwCalcFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_LPF_REVERB | X3DAUDIO_CALCULATE_REVERB;
		X3DAudioCalculate(m_3dAudioHandle, &m_3dListener, &emitter, dwCalcFlags, dsp);

		IXAudio2SourceVoice* voice = sound->GetBody();
		if (voice != nullptr)
		{
			voice->SetOutputMatrix(m_masteringVoice, sound->GetInputChannelNum(), m_channelNum, dsp->pMatrixCoefficients);
			voice->SetFrequencyRatio(dsp->DopplerFactor);
			XAUDIO2_FILTER_PARAMETERS FilterParametersDirect = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dsp->LPFDirectCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
			voice->SetOutputFilterParameters(m_masteringVoice, &FilterParametersDirect);
		}
	}
}

IXAudio2SourceVoice* SoundEngine::CreateSouceVoice(WAVEFORMATEX* format, bool is3DSound)
{
	if (!is3DSound)
	{
		IXAudio2SourceVoice* sourceVoice;
		m_xAudio->CreateSourceVoice(&sourceVoice, format);
		return sourceVoice;
	}
	else
	{
		XAUDIO2_SEND_DESCRIPTOR sendDescriptors;
		sendDescriptors.Flags = XAUDIO2_SEND_USEFILTER;
		sendDescriptors.pOutputVoice = m_masteringVoice;

		XAUDIO2_VOICE_SENDS sendList = { 1, &sendDescriptors };
		IXAudio2SourceVoice* sourceVoice;
		m_xAudio->CreateSourceVoice(&sourceVoice, format, 0, 2.0f, NULL, &sendList);
		return sourceVoice;
	}
}