#pragma once
class WaveFileOpen
{
public:
	//コンストラクタ
	WaveFileOpen();

	//デストラクタ
	~WaveFileOpen();

	/*
	ファイルを開いて読み込み
	fileName	開くWAVEファイルのパス
	*/
	void Open(char* fileName);

	//フォーマットを取得
	WAVEFORMATEX* GetFormat()
	{
		return m_format;
	}

	//データサイスを取得
	DWORD GetSize()
	{
		return m_size;
	}

	//読み込み用のバッファを取得
	char* GetSoundData()
	{
		return m_readMemory.get();
	}

private:

	void Read();

private:
	HMMIO							m_hmmio;			//WAVEファイルのハンドル
	MMCKINFO						m_riffChunk;		//一番親のチャンク
	MMCKINFO						m_dataChunk;		//波形データを持つチャンク
	DWORD							m_size;				//データのサイズ
	std::unique_ptr<char[]>			m_readMemory;		//データを読み込む用のバッファ
	WAVEFORMATEX*					m_format;			//WAVEファイルのフォーマット
};