#pragma once
//プレイヤークラス
#include "PlayerGraspCliff.h"
#include "PlayerWallJump.h"
class GhostPlayer;

enum EnAnimationSet
{
	enAnimSetRun,
	enAnimSetWait,
	enAnimSetWallShear,
	enAnimSetWallJump,
	enAnimSetJump,
	enAnimSetCliffRise,
	enAnimSetVerticalJump,
	enAnimSetDelight,
	enAnimSetNum,
};
class MapChip;


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
	bool Start() override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	//描画関数
	void AfterDraw() override;

	//座標を取得
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}

	/*
	ステージギミックによりプレイヤーが動かされる時の移動速度を設定。
	moveSpeed	プレイヤーを動かす方向と速度
	*/
	void SetStageGimmickMoveSpeed(const D3DXVECTOR3& moveSpeed);

	/*
	ボーンの名前検索でボーンのワード行列を取得。
	boneName	ボーンの名前
	ret			ボーンのワールド行列のポインタ
	*/
	const D3DXMATRIX* FindBoneWorldMatrix(const char* boneName) const
	{
		return m_skinModelData.GetFindBoneWorldMatrix(boneName);
	}

	//ワールド行列を取得。
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

	//1フレームでの移動量を取得。
	const D3DXVECTOR3& GetMovement() const
	{
		return m_movement;
	}

	/*
	崖を上るときにPlayerGraspCliffから呼び出す関数
	moveDirection	壁の法線
	*/
	void CliffRiseStart(const D3DXVECTOR3& moveDirection);

	/*
	崖を上っている時にPlayerGraspCliffから呼び出す関数
	ret		崖を上り終わったか？trueなら上り終わった、falseならまだ上っている途中
	*/
	bool CriffRiseEnd();

	/*
	壁に張り付いた時に呼び出す関数
	playerDirection		プレイヤーの方向
	*/
	void WallShear(const D3DXVECTOR3& playerDirection);

	/*
	壁ジャンプする時に呼び出す関数
	jumpDirection		プレイヤーがジャンプする方向
	*/
	void WallJump(const D3DXVECTOR3& jumpDirection);

	/*
	親子関係をつけたり外したりする関数
	parent　		親のポインタ。親子関係を外す場合はnullptrを渡せばいい。
	parentRotation	回転も親子関係をつけるか否か
	return			親子関係がついたか？trueならついた、falseなら親子関係つけるのに失敗したか親子関係が切れた
	*/
	bool SetParent(const MapChip* parent, bool parentRotation);

	//モデルデータを取得
	const SkinModelData& GetSkinModelData() const
	{
		return m_skinModelData;
	}

	/*
	ゴーストデータの計測開始
	time	ステージのクリアタイム
	isClear	ステージをクリアしたか？
	*/
	void GhostDataFinish(float time, bool isClear) const;

	//ゴーストデータの計測開始
	void GhostDataStart() const;

	//ライトを取得
	const Light& GetLight() const
	{
		return m_light;
	}

	void MoveSpeedDelay()
	{
		m_delayTime = 6.0f;
	}

	void Invincible();
	
	void BlowObstacle();
private:
	//移動処理をする関数
	void Move(float deltaTime);

	//モデルを移動方向に合わせてディレイをかけながら回転させる関数
	void DelayRotation(const D3DXVECTOR3& rotationDirection);

	//モデルを移動方向に合わせて回転させる関数
	void Rotation(const D3DXVECTOR3& rotationDirection);

	void PlayAnimation(EnAnimationSet animationSet);

private:
	SkinModel			m_skinModel;			//スキンモデル
	SkinModelData		m_skinModelData;		//スキンモデルデータ
	Light				m_light;				//モデルのライト
	D3DXQUATERNION		m_rotation;				//モデルの回転
	D3DXQUATERNION		m_localRotation;		//親がいるときの親から見たローカル座標
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_localPosition;		//親がいるときの親から見たローカルな回転
	D3DXVECTOR3			m_scale;				//モデルのサイズ
	Animation			m_anim;					//アニメーション
	CharacterController m_characterController;	//キャラクターコントローラー
	D3DXVECTOR3			m_stageGimmickMoveSpeed;//ステージギミックによってプレイヤーを動かされる時の移動速度
	D3DXVECTOR3			m_movement;				//1フレームで移動した距離
	PlayerWallJump		m_wallJump;				//壁ジャンプしてくれる奴
	int					m_jumpCount;			//ジャンプした回数
	EnAnimationSet		m_currentAnim;			//現在再生してるアニメーション
	bool				m_isJump;				//ジャンプしてるか？
	const MapChip*		m_parent;				//親
	bool				m_isParentRotation;		//回転の親子関係をつけているか
	float				m_moveSpeed;			//移動速度
	float				m_acceleration;			//加速度
	const int			m_rotationFrameNum;		//回転を線形補間する時に使うフレーム数
	float				m_frameAngle;			//1フレームで回転する回転量
	int					m_rotationCount;		//回転を線形補間するためのカウンター
	const float			m_jumpSpeed;
	float				m_delayTime;
	bool				m_isInvincible;			
	float				m_invincibleTime;
	bool				m_isObstacle;
	float				m_obstacleTime;
};






