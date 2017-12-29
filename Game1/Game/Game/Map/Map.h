#pragma once
class MapChip;
class Player;

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

	//初期化関数
	void Start()override;

	//更新関数
	void Update()override;

	//死ぬ前に一度だけ呼ばれる
	void BeforeDead()override;

	//プレイヤーを取得
	Player* GetPlayer()
	{
		return m_player;
	}

	int IntMakeHash(char* string);

private:
	std::vector<MapChip*> m_mapChip;	//マップチップ
	Player*	m_player;					//プレイヤー
	
};
