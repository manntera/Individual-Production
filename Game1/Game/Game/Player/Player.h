#pragma once
//プレイヤークラス
#include "PlayerGraspCliff.h"
#include "PlayerWallJump.h"

enum EnAnimationSet
{
	enAnimSetRun,
	enAnimSetWait,
	enAnimSetWallShear,
	enAnimSetWallJump,
	enAnimSetJump,
	enAnimSetCliffRise,
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

	D3DXMATRIX* FindBoneWorldMatrix(char* boneName)
	{
		return m_skinModelData.GetFindBoneWorldMatrix(boneName);
	}

	D3DXMATRIX GetWorldMatrix()
	{
		return m_skinModel.GetWorldMatrix();
	}


	D3DXVECTOR3 GetMovement()
	{
		return m_movement;
	}
	/*
	崖を上るときにPlayerGraspCliffから呼び出す関数
	moveDirection	壁の法線
	*/
	void CliffRiseStart(D3DXVECTOR3 moveDirection);

	/*
	崖を上っている時にPlayerGraspCliffから呼び出す関数
	ret		崖を上り終わったか？trueなら上り終わった、falseならまだ上っている途中
	*/
	bool CriffRiseEnd();

	void WallShear(D3DXVECTOR3 moveSpeed);

	void WallJump(D3DXVECTOR3 jumpDirection);

	void SetParent(MapChip* parent);

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
	D3DXQUATERNION		m_localRotation;
	D3DXVECTOR3			m_position;				//座標
	D3DXVECTOR3			m_localPosition;
	D3DXVECTOR3			m_scale;				//モデルのサイズ
	Animation			m_anim;					//アニメーション
	CharacterController m_characterController;	//キャラクターコントローラー
	Texture				m_modelNormalMap;		//モデルの法線マップ
	Texture				m_modelSpecularMap;		//モデルのスペキュラマップ
	D3DXVECTOR3			m_stageGimmickMoveSpeed;//ステージギミックによってプレイヤーを動かされる時の移動速度
	D3DXVECTOR3			m_movement;
	PlayerGraspCliff	m_graspCliff;
	PlayerWallJump		m_wallJump;
	int					m_jumpCount;
	float				m_wallShearGravity;
	float				m_defaultGravity;
	EnAnimationSet		m_currentAnim;
	bool				m_isJump;
	float				m_animationTime = 0.3f;
	MapChip*			m_parent;
};