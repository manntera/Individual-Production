#pragma once
#include "Animation.h"

class SkinModelData;
class RenderContext;
class Light;

class SkinModel
{
public:
	//コンストラクタ
	SkinModel();

	//デストラクタ
	~SkinModel();

	/*
	初期化関数
	modelData		モデルを読み込んだデータ
	*/
	void Init(SkinModelData* modelData);

	/*
	描画関数
	viewMatrix		カメラのビュー行列
	projMatrix		カメラのプロジェクション行列
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);

	/*
	ワールド行列を更新。
	trans	平行移動
	rot		回転
	scale	拡大
	*/
	void UpdateWorldMatrix(D3DXVECTOR3 trans, D3DXQUATERNION rot, D3DXVECTOR3 scale);

	/*
	ライトを設定
	*/
	void SetLight(Light *light)
	{
		this->m_light = light;
	}

	//ワールド行列を取得。
	D3DXMATRIX GetWorldMatrix()
	{
		return m_worldMatrix;
	}
	/*
	オリジナルメッシュの先頭を取得する
	*/
	LPD3DXMESH GetOrgMeshFirst();

private:
	D3DXMATRIX		m_worldMatrix;				//ワールド行列
	D3DXMATRIX		m_rotationMatrix;				//回転行列
	SkinModelData*	m_skinModelData;				//スキンモデルデータ
	ID3DXEffect*	m_pEffect;					//エフェクト
	Animation		m_animation;					//アニメーション
	Light*			m_light;						//ライト
};