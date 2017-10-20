#pragma once
#include "WaveFileOpen.h"

class SoundSource : public GameObject
{
public:
	//コンストラクタ
	SoundSource();

	//デストラクタ
	~SoundSource();

	/*
	初期化
	filePath		読み込みたいWaveファイルのパス
	*/
	void Init(char* filePath);

	//更新
	void Update()override;

	/*
	再生
	isLoop		ループさせるか？trueならループ、falseならループしない
	*/
	void Play(bool isLoop);

private:
	IXAudio2SourceVoice*	m_sourceVoice;		//ソースボイス
	WaveFileOpen			m_waveFile;			//WAVEファイルのデータ
	bool					m_isLoop;			//ループフラグ
	bool					m_isPlaying;		//再生中か？
};