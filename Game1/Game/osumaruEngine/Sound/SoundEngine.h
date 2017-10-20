#pragma once
//サウンドエンジン

class SoundEngine : Uncopyable
{
public:

	//コンストラクタ
	SoundEngine();

	//デストラクタ
	~SoundEngine();

	//初期化
	void Init();

	/*
	ソースボイスを作成
	format	waveファイルのフォーマット
	ret		作ったソースボイスを返す
	*/
	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format);

private:
	IXAudio2*				m_xAudio;			//オーディオ
	IXAudio2MasteringVoice* m_masteringVoice;	//マスターボイス
};
