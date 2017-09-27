#pragma once
//プレイヤークラス

class Player : public GameObject
{
public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	/*
	初期化関数
	position	プレイヤーの座標
	rotation	プレイヤーの回転
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
	
	//初期化関数
	void Start() override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	//座標を取得
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}

private:
	//移動処理をする関数
	void Move();

	//モデルを移動方向に合わせて回転させる関数
	void Rotation();

private:
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	Light				m_light;				//モデルのライト
	D3DXQUATERNION		m_rotation;				//モデルの回転
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_scale;				//モデルのサイズ
	Animation			m_anim;					//アニメーション
	CharacterController m_characterController;	//キャラクターコントローラー
	Texture				m_modelNormalMap;		//モデルの法線マップ
	Texture				m_modelSpecularMap;		//モデルのスペキュラマップ
};