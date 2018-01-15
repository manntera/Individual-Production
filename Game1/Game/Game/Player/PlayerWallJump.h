#pragma once
//プレイヤーの壁ずりや壁ジャンプをするクラス
class Player;


class PlayerWallJump
{
public:

	//コンストラクタ
	PlayerWallJump();

	//デストラクタ
	~PlayerWallJump();

	/*
	初期化
	player					プレイヤー
	characterController		プレイヤーのキャラコン
	*/
	void Init(Player* player, CharacterController* characterController);

	//更新
	void Update();

	//壁ずり中か？
	bool IsWallShear()
	{
		return m_isWallShear;
	}

	//壁ジャンプしたか
	bool IsWallJump()
	{
		return m_isWallJump && m_wallJumpCount ==0;
	}

	//描画関数
	void Draw();

private:

	BoxCollider				m_groundCollider;		//地面とのあたり判定を取るコライダー
	BoxCollider				m_wallCollider;			//壁とのあたり判定を取るコライダー
	CollisionDetection		m_wallDetection;		//壁とのあたり判定
	CollisionDetection		m_groundDetection;		//地面とのあたり判定(キャラクターコントローラーのIsOnGroundを使うとメッシュなどで剛体を作っていた場合にポリゴンの切れ目に判定が入ってしまう
	Player*					m_player;				//プレイヤー
	bool					m_isWallShear;			//壁ずり中か？
	bool					m_isWallJump;			//壁ジャンプ中か？
	CharacterController*	m_characterController;	//プレイヤーのキャラクターコントローラー
	D3DXVECTOR3				m_wallJumpDirection;	//壁ジャンプするときの方向
	float					m_wallShearGravity;		//壁ずりの時の重力
	float					m_defaultGravity;		//普通の時の重力
	ParticleEmitter*		m_wallDust;				//パーティクル
	D3DXMATRIX*				m_dustPos;				//パーティクルを出す時の位置
	int						m_wallJumpCount;		//壁ジャンプしてからのカウンター
};