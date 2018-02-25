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
	
	//3Dサウンドリストに追加
	void Add3dSound(SoundSource* sound)
	{
		m_3dSound.push_back(sound);
	}

	//3Dサウンドリストから削除
	void Delete3dSound(SoundSource* sound)
	{
		auto& it = std::find(m_3dSound.begin(), m_3dSound.end(), sound);
		if (it != m_3dSound.end())
		{
			m_3dSound.erase(it);
		}
	}

	//リスナーの座標を設定
	void SetListenerPosition(const D3DXVECTOR3& position)
	{
		m_3dListener.Position.x = position.x;
		m_3dListener.Position.y = position.y;
		m_3dListener.Position.z = position.z;
	}

	//リスナーの前方向を設定
	void SetListenerFront(const D3DXVECTOR3& front)
	{
		m_3dListener.OrientFront.x = front.x;
		m_3dListener.OrientFront.y = front.y;
		m_3dListener.OrientFront.z = front.z;
	}

	//リスナーの上方向を設定
	void SetListenerUp(const D3DXVECTOR3& up)
	{
		m_3dListener.OrientTop.x = up.x;
		m_3dListener.OrientTop.y = up.y;
		m_3dListener.OrientTop.z = up.z;
	}

	/*
	ソースボイスを作成
	format	waveファイルのフォーマット
	ret		作ったソースボイスを返す
	*/
	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format, bool is3DSound);

	DWORD GetChannelNum()
	{
		return m_channelNum;
	}

private:
	DWORD					m_channelNum;
	X3DAUDIO_LISTENER		m_3dListener;		//リスナー
	X3DAUDIO_HANDLE			m_3dAudioHandle;	//３Dサウンドのハンドル
	std::list<SoundSource*> m_3dSound;			//3Dサウンドのリスト
	IXAudio2*				m_xAudio;			//オーディオ
	IXAudio2MasteringVoice* m_masteringVoice;	//マスターボイス
};
