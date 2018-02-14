#pragma once
class MapChip;
class Player;
//マップチップのタグ
enum EnMapChipTag
{
	enMapTagUntagged,
	enMapTagPlayer,
	enMapTagFall,
	enMapTagGoal,
	enMapTagMapChip,
	enMapTagMoveFloor,
	enMapTagSpring,
	enMapTagRotation,
	enMapTagHindrance,
	enMapTagScoreUp,
	enMapTagStopTime,
	enMapTagGoalObject,
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

private:
	std::list<MapChip*> m_mapChip;					//マップチップ
	Player*				m_player;					//プレイヤー
	float				m_stopTime;					//ステージギミックを止めてる間のカウンター
	bool				m_isLoad;					//モデルの読み込めたかのフラグ
};
