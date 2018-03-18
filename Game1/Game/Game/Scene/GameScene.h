#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;
class TimeSprite;
class GhostPlayer;
//遊べるステージの最大数
const int STAGE_NUM = 5;

//ゲームシーンクラス
class GameScene : public GameObject
{
private:
	//コンストラクタ
	GameScene();

	//デストラクタ
	~GameScene();

public:

	//インスタンスを取得
	static GameScene& GetInstance()
	{
		static GameScene gameScene;
		return gameScene;
	}

	/*
	初期化関数
	*/
	void Init(int stageNum, bool isTimeAttack);

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//死ぬ前に一度だけ呼ばれる関数
	void BeforeDead()override;

	//描画関数
	void AfterDraw()override;
	
	//カメラの取得
	const Camera& GetCamera() const;

	//プレイヤーの取得
	const Player* GetPlayer() const;

	//ゲームクリアするときに外部から呼び出す関数
	void GameClear();

	//ゲームオーバーの時に外部から呼び出す関数
	void GameOver();

	void GhostDataFinish();

	//今のステージの番号を取得
	int GetStageNum() const
	{
		return m_stageNum;
	}

	//今解放されているステージの最大数
	int GetStageMaxNum() const
	{
		return m_stageMaxNum;
	}

	//ゲームシーンを作成
	void Create()
	{
		Add(this, LAST_PRIORITY);
		m_isActive = true;
	}

	//アクティブか？
	bool IsActive() const
	{
		return m_isActive;
	}

	//他のロードが終わったらこの関数を呼ぶ
	void LoadComp()
	{
		m_isLoad = true;
	}

	//再生を一時停止
	void SoundStop()
	{
		m_pBgm->Stop();
	}

	//サウンドを再生
	void SoundPlay()
	{
		m_pBgm->Play(true);
	}

private:	
	bool						m_isGameOver;			//ゲームオーバーか？
	bool						m_isGameClear;			//ゲームクリアか？
	Map*						m_pMap;					//マップ
	GameCamera*					m_pCamera;				//カメラ
	Sky*						m_pSky;					//スカイボックス
	SoundSource*				m_pBgm;					//BGM
	int							m_stageNum;				//現在のステージの番号
	int							m_stageMaxNum;			//一番進んでいるステージの番号
	TimeSprite*					m_pTimeSprite;			//タイム表示のスプライト
	bool						m_isInit;				//初期化したか？
	bool						m_isTimeAttack;			//タイムアタックか？
	GhostPlayer*				m_pGhost;				//ゴーストプレイヤー
	bool						m_isActive;				//生きてるか死んでるか
	bool						m_isLoad;				//ロードが終わったか
	bool						m_isTimeAttackStart;	//タイムアタックモードの時にゲームがスタートしてるか？
	std::unique_ptr<Sprite>		m_pSprite;				//タイムアタックが始まる前の準備中表示のスプライト
};

//ゲームシーンを取得。
static GameScene& GetGameScene()
{
	return GameScene::GetInstance();
}