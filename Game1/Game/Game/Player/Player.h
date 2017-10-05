#pragma once
//プレイヤークラス

enum EnAnimationSet
{
	enAnimSetRun,
	enAnimSetWait,
	enAnimSetWallShear,
	enAnimSetWallJump,
	enAnimSetJump,
	enAnimSetNum,
};

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

	/*
	ステージギミックによりプレイヤーが動かされる時の移動速度を設定。
	moveSpeed	プレイヤーを動かす方向と速度
	*/
	void SetStageGimmickMoveSpeed(D3DXVECTOR3 moveSpeed);

private:
	//移動処理をする関数
	void Move();

	void Jump();

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
	D3DXVECTOR3			m_stageGimmickMoveSpeed;//ステージギミックによってプレイヤーを動かされる時の移動速度
	int					m_jumpCount;
	bool				m_isWallShear;
	float				m_wallShearGravity;
	float				m_defaultGravity;
	D3DXVECTOR3			m_wallJumpDirection;
	EnAnimationSet		m_currentAnim;
};