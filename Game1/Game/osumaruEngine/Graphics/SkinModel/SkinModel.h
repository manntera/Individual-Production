#pragma once
#include "Animation.h"

class Camera;
class SkinModelData;
class RenderContext;
class Light;
class Texture;
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
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, int num);

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

	//法線マップをセット
	void SetNormalMap(Texture* texture)
	{
		m_pNormalMap = texture;
		m_isHasNormalMap = true;
	}

	//スペキュラマップを設定
	void SetSpecularMap(Texture* texture, Camera* camera)
	{
		m_pSpecularMap = texture;
		m_pCamera = camera;
		m_isHasSpecularMap = true;
	}
public:


	bool			m_isShadowMapCaster;
	bool			m_isShadowMapReceiver;

private:
	Texture*		m_pNormalMap;
	Texture*		m_pSpecularMap;
	bool			m_isHasNormalMap;
	bool			m_isHasSpecularMap;
	D3DXMATRIX		m_worldMatrix;				//ワールド行列
	D3DXMATRIX		m_rotationMatrix;				//回転行列
	SkinModelData*	m_skinModelData;				//スキンモデルデータ
	ID3DXEffect*	m_pEffect;					//エフェクト
	Animation		m_animation;					//アニメーション
	Light*			m_light;						//ライト
	Camera*			m_pCamera;

};