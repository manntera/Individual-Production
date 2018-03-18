#pragma once
//空のクラス

class Sky : public GameObject
{
public:

	//コンストラクタ
	Sky();

	//デストラクタ
	~Sky();

	void Init(int stageNum);

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;
private:

	SkinModel		m_skinModel;			//スキンモデル
	SkinModelData	m_skinModelData;		//スキンモデルデータ
	D3DXVECTOR3		m_position;				//座標
	D3DXQUATERNION	m_rotation;				//回転
	D3DXVECTOR3		m_scale;				//拡大
	Light			m_light;				//モデルのライト
	int				m_stageNum;				//ステージの番号
};