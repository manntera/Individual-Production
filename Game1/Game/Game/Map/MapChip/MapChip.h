#pragma once
//マップで配置するオブジェクトの基底クラス

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
	*/
	virtual void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName);

	//初期化関数
	virtual void Start()override;

	//更新関数
	virtual void Update()override;

	//描画関数
	virtual void Render()override;


protected:
	SkinModelData	m_skinModelData;
	SkinModel		m_skinModel;
	Light			m_light;
	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
};