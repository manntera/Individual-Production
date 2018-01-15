#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;
class TimeSprite;
class GhostPlayer;

//ゲームシーンクラス

class GameScene : public GameObject
{
public:
	//コンストラクタ
	GameScene();

	//デストラクタ
	~GameScene();

	void Init(int stageNum, bool isTimeAttack);

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//死ぬ前に一度だけ呼ばれる関数
	void BeforeDead()override;
	
	//カメラの取得
	Camera& GetCamera();

	//プレイヤーの取得
	Player* GetPlayer();

	//ゲームクリアするときに外部から呼び出す関数
	void GameClear();

	//ゲームオーバーの時に外部から呼び出す関数
	void GameOver();

	void GhostDataFinish();

	//今のステージの番号を取得
	static int GetStageNum()
	{
		return m_stageNum;
	}

	static int GetStageMaxNum()
	{
		return m_stageMaxNum;
	}

private:

	bool			m_isGameOver;	//ゲームオーバーか？
	bool			m_isGameClear;	//ゲームクリアか？
	Map*			m_map;			//マップ
	GameCamera*		m_camera;		//カメラ
	Sky*			m_sky;			//スカイボックス
	SoundSource*	m_bgm;			//BGM
	static int		m_stageNum;		//現在のステージの番号
	static int		m_stageMaxNum;	//一番進んでいるステージの番号
	TimeSprite*		m_pTimeSprite;	//タイム表示のスプライト
	bool			m_isInit;		//初期化したか？
	bool			m_isTimeAttack;	//タイムアタックか？
	GhostPlayer*	m_pGhost;		//ゴーストプレイヤー
};
const int STAGE_NUM = 3;
extern GameScene *g_gameScene;