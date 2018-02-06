#pragma once
//サウンドエンジン
class SoundSource;
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//最大出力チャンネル数。

class SoundEngine : Uncopyable
{
public:

	//コンストラクタ
	SoundEngine();

	//デストラクタ
	~SoundEngine();

	//初期化
	void Init();

	//更新関数
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
	ソースボイスを作成
	format	waveファイルのフォーマット
	ret		作ったソースボイスを返す
	*/
	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format, bool is3DSound);

private:
	DWORD					m_channelNum;
	X3DAUDIO_LISTENER		m_3dListener;
	X3DAUDIO_HANDLE			m_3dAudioHandle;
	std::list<SoundSource*> m_3dSound;
	IUnknown*				m_reverbEffect;	
	IXAudio2*				m_xAudio;			//オーディオ
	IXAudio2MasteringVoice* m_masteringVoice;	//マスターボイス
	IXAudio2SubmixVoice*	m_submixVoice;
};
