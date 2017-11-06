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

	//
	bool IsWallJump()
	{
		return m_isWallJump;
	}

private:
	BoxCollider				m_boxCollider;			//壁とのあたり判定を取るコライダー
	CollisionDetection		m_wallDetection;		//壁とのあたり判定
	Player*					m_player;				//プレイヤー
	bool					m_isWallShear;			//壁ずり中か？
	bool					m_isWallJump;			//壁ジャンプ中か？
	CharacterController*	m_characterController;	//プレイヤーのキャラクターコントローラー
	D3DXVECTOR3				m_wallJumpDirection;	//壁ジャンプするときの方向
	float					m_wallShearGravity;		//壁ずりの時の重力
	float					m_defaultGravity;		//普通の時の重力
	ParticleEmitter*		m_wallDust;
	D3DXMATRIX*				m_dustPos;
};