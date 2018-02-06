#pragma once
class Player;
//プレイヤーが崖をつかむ処理をするクラス

class PlayerGraspCliff
{
public:

	//コンストラクタ
	PlayerGraspCliff();

	//デストラクタ
	~PlayerGraspCliff();

	/*
	初期化関数
	player		使うプレイヤー
	height		プレイヤーの高さ
	*/
	void Init(Player* player, float height);

	//更新関数
	void Update();

	//崖を上っているか？
	bool IsActive() const
	{
		return m_isActive;
	}

	//描画関数
	void Draw();

private:	
	CollisionDetection	m_cliffRiseDetectionLow;	//崖をつかんだかのあたり判定
	CollisionDetection	m_cliffRiseDetectionUp;		//崖をつかんだかのあたり判定
	CollisionDetection  m_cliffRiseDetectionBack;	//崖をつかんだ乾せいかのあたり判定
	BoxCollider			m_boxCollider;				//当たり判定に使うコライダー
	Player*				m_player;					//プレイヤー
	float				m_playerHeight;				//プレイヤーの高さ
	bool				m_isActive;					//崖を上っているか？trueなら上っている途中、falseなら上っていない
};