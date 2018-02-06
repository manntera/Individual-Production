#pragma once
//マップで配置するオブジェクトの基底クラス
class Map;
class Player;

class MapChip : public GameObject
{
public:

	//コンストラクタ
	MapChip();

	//デストラクタ
	virtual ~MapChip();

	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	virtual void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr);

	//初期化関数
	virtual bool Start()override;

	//更新関数
	virtual void Update()override;

	//描画関数
	virtual void Draw()override;

	const D3DXMATRIX GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}
	
	/*
	イテレーターをセット
	map			自身をデリートするためのインスタンス
	iterator	自身のイテレーター
	*/
	void SetIterator(Map* map, std::list<MapChip*>::iterator iterator);

	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

	void SetPlayer(Player* player)
	{
		m_pPlayer = player;
	}

protected:
	//デリートする関数
	void MapChipDelete();

protected:

	SkinModelData	m_skinModelData;			//スキンンモデルデータ
	SkinModel		m_skinModel;				//スキンモデル
	Light			m_light;					//モデルのライト
	D3DXVECTOR3		m_position;					//座標
	D3DXQUATERNION	m_rotation;					//回転
	D3DXVECTOR3		m_scale;					//拡大
	Map*			m_pMap;						//デリートする時のためのポインタ
	std::list<MapChip*>::iterator m_iterator;	//自身のイテレーター
	bool			m_isActive;					//アクティブか？
	Player*			m_pPlayer;					//プレイヤーのインスタンス(親子関係をつけたりするときに使う)
};