#pragma once
#include "Animation.h"

class Camera;
class SkinModelData;
class RenderContext;
class Light;
class Texture;

struct ShaderTechnique
{
	D3DXHANDLE NoSkinModelTechnique;		//スキンあり
	D3DXHANDLE SkinModelTechnique;			//スキンなし
};

//シェーダーテクニック
enum EnSkinModelShaderTechnique
{
	enShaderTechniqueNormal,				//普通に描画するときのテクニック
	enShaderTechniqueShadow,				//影を書く時のテクニック
	enShaderTechniqueSilhouette,
	enShaderTechniqueNum,
};
class SkinModel : Uncopyable
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

	//シャドウマップに登録
	void ShadowMapEntry();


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

	/*
	影を落とすかを設定
	isShadowCaster		trueならシャドウマップに登録、falseならシャドウマップから削除
	*/
	void SetShadowCasterFlg(bool isShadowCaster)
	{
		m_isShadowMapCaster = isShadowCaster;
	}

	/*
	影を落とされるかを設定
	isShadowReceiver	trueなら影を落とされる、falseなら影を落とさない
	*/
	void SetShadowReceiverFlg(bool isShadowReceiver)
	{
		m_isShadowMapReceiver = isShadowReceiver;
	}

	/*
	シェーダーテクニックを設定
	shaderTechnique		設定するシェーダーテクニック
	*/
	void SetShaderTechnique(EnSkinModelShaderTechnique shaderTechnique)
	{
		m_currentShaderTechnique = shaderTechnique;
	}

	//今のシェーダーテクニックを取得
	EnSkinModelShaderTechnique GetCurrentShaderTechnique()
	{
		return m_currentShaderTechnique;
	}
private:
	bool						m_isShadowMapCaster;						//影を落とすか？
	bool						m_isShadowMapReceiver;						//影を落とされるか？
	ShaderTechnique				m_shaderTechnique[enShaderTechniqueNum];	//シェーダーテクニックの配列
	EnSkinModelShaderTechnique	m_currentShaderTechnique;					//現在のシェーダーテクニック
	Texture*					m_pNormalMap;								//法線マップ
	Texture*					m_pSpecularMap;								//スペキュラマップ
	bool						m_isHasNormalMap;							//法線マップを持っているか？
	bool						m_isHasSpecularMap;							//スペキュラマップを持っているか？	
	D3DXMATRIX					m_worldMatrix;								//ワールド行列
	D3DXMATRIX					m_rotationMatrix;							//回転行列
	SkinModelData*				m_skinModelData;							//スキンモデルデータ
	ID3DXEffect*				m_pEffect;									//エフェクト
	Animation					m_animation;								//アニメーション
	Light*						m_light;									//ライト
	Camera*						m_pCamera;									//スペキュラで使うカメラ
	bool						m_isShadowCompesation;						//
};