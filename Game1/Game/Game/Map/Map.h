#pragma once
class MapChip;
class Player;
//マップチップのタグ
enum EnMapChipTag
{
	enMapTagUntagged,
	enMapTagPlayer,
	enMapTagFall1,
	enMapTagFall2,
	enMapTagFall3,
	enMapTagGoal,
	enMapTagMapChip,
	enMapTagMoveFloor,
	enMapTagSpring,
	enMapTagRotation,
	enMapTagHindrance,
	enMapTagScoreUp,
	enMapTagStopTime,
	enMapTagGoalObject,
	enMapTagBlowObstacle,
	enMapTagInvincibleItem,
	enMapTagPlayerDelayItem,
	enMapTagNum,
};

//マップのオブジェクトを配置するクラス

class Map : public GameObject
{
public:
	//コンストラクタ
	Map();

	//デストラクタ
	~Map();

	//初期化
	void Init(int stageNum);


	//更新関数
	void Update()override;

	//死ぬ前に一度だけ呼ばれる
	void BeforeDead()override;

	//プレイヤーを取得
	const Player* GetPlayer() const
	{
		return m_player;
	}
	
	/*
	マップチップをデリート
	iterator	デリートするマップチップのイテレーター
	*/
	void MapChipErase(std::list<MapChip*>::iterator iterator);

	//時間を止める関数
	void StopTime();

	//プレイヤーのアクティブフラグを設定
	void SetIsPlayerActive(bool isActive);

private:
	std::list<MapChip*> m_mapChip;					//マップチップ
	Player*				m_player;					//プレイヤー
	float				m_stopTime;					//ステージギミックを止めてる間のカウンター
	bool				m_isLoad;					//モデルの読み込めたかのフラグ
	float				m_soundTimer;				//ステージギミックを止めた時の時計の音のインターバルを測る
	float				m_soundTimeLimit;			//音を鳴らすまでの時間
	const float			m_stopTimeLimit;			//ステージギミックを止めてる間の時間
};
