#pragma once
//空のクラス

class Sky : public GameObject
{
public:

	//コンストラクタ
	Sky();

	//デストラクタ
	~Sky();

	//初期化関数
	void Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;
private:

	SkinModel		m_skinModel;			//スキンモデル
	SkinModelData	m_skinModelData;		//スキンモデルデータ
	Light			m_light;				//モデルのライト
};