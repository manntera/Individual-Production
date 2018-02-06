#pragma once
//�T�E���h�G���W��
class SoundSource;
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B

class SoundEngine : Uncopyable
{
public:

	//�R���X�g���N�^
	SoundEngine();

	//�f�X�g���N�^
	~SoundEngine();

	//������
	void Init();

	//�X�V�֐�
	void Update();

	void Add3dSound(SoundSource* sound)
	{
		m_3dSound.push_back(sound);
	}

	void Delete3dSound(SoundSource* sound)
	{
		auto& it = std::find(m_3dSound.begin(), m_3dSound.end(), sound);
		if (it != m_3dSound.end())
		{
			m_3dSound.erase(it);
		}
	}

	void SetListenerPosition(D3DXVECTOR3 position)
	{
		m_3dListener.Position.x = position.x;
		m_3dListener.Position.y = position.y;
		m_3dListener.Position.z = position.z;
	}

	void SetListenerFront(D3DXVECTOR3 front)
	{
		m_3dListener.OrientFront.x = front.x;
		m_3dListener.OrientFront.y = front.y;
		m_3dListener.OrientFront.z = front.z;
	}

	void SetListenerUp(D3DXVECTOR3 up)
	{
		m_3dListener.OrientTop.x = up.x;
		m_3dListener.OrientTop.y = up.y;
		m_3dListener.OrientTop.z = up.z;
	}
	DWORD GetChannelNum()
	{
		return m_channelNum;
	}
	/*
	�\�[�X�{�C�X���쐬
	format	wave�t�@�C���̃t�H�[�}�b�g
	ret		������\�[�X�{�C�X��Ԃ�
	*/
	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format, bool is3DSound);

private:
	DWORD					m_channelNum;
	X3DAUDIO_LISTENER		m_3dListener;
	X3DAUDIO_HANDLE			m_3dAudioHandle;
	std::list<SoundSource*> m_3dSound;
	IUnknown*				m_reverbEffect;	
	IXAudio2*				m_xAudio;			//�I�[�f�B�I
	IXAudio2MasteringVoice* m_masteringVoice;	//�}�X�^�[�{�C�X
	IXAudio2SubmixVoice*	m_submixVoice;
};
