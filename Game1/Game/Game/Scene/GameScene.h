#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;
class TimeSprite;

//ゲームシーンクラス

class GameScene : public GameObject
{
public:
	//コンストラクタ
	GameScene();

	//デストラクタ
	~GameScene();

	//初期化関数
	void Start()override;

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

private:

	bool			m_isGameOver;	//ゲームオーバーか？
	bool			m_isGameClear;	//ゲームクリアか？
	Map*			m_map;		//マップ
	GameCamera*		m_camera;	//カメラ
	Sky*			m_sky;		//スカイボックス
	SoundSource*		m_bgm;	//BGM
	static int		m_stageNum;
	TimeSprite*		m_pTimeSprite;
};

extern GameScene *g_gameScene;