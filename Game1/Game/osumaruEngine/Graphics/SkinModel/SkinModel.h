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
	enShaderTechniqueDithering,
	enShaderTechniqueGhost,
	enShaderTechniquePlayer,
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
	void Draw(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

	/*
	ワールド行列を更新。
	trans	平行移動
	rot		回転
	scale	拡大
	*/
	void UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	/*
	更新。
	trans	平行移動
	rot		回転
	scale	拡大
	*/
	void Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	//シャドウマップに登録
	void ShadowMapEntry();


	/*
	ライトを設定
	*/
	void SetLight(const Light *light)
	{
		this->m_pLight = light;
	}

	//ワールド行列を取得。
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}
	/*
	オリジナルメッシュの先頭を取得する
	*/
	const LPD3DXMESH GetOrgMeshFirst() const;

	//法線マップをセット
	void SetNormalMap(const Texture* texture)
	{
		m_pNormalMap = texture;
		m_isHasNormalMap = true;
	}

	//スペキュラマップを設定
	void SetSpecularMap(const Texture* texture, const Camera* camera)
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
	EnSkinModelShaderTechnique GetCurrentShaderTechnique() const
	{
		return m_currentShaderTechnique;
	}

	//地面に垂直な部分があるモデルかのフラグを設定
	void SetShadowCompesationFlg(bool isShadowCompesation)
	{
		m_isShadowCompesation = isShadowCompesation;
	}

	//地面に垂直な部分があるモデルか？
	bool IsShadowCompesation() const
	{
		return m_isShadowCompesation;
	}


	//座標の取得。
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}

	//スケールの取得。
	const D3DXVECTOR3& GetScale() const
	{
		return m_scale;
	}

	//回転を取得。
	const D3DXQUATERNION& GetRotation() const
	{
		return m_rotation;
	}


private:
	bool						m_isShadowMapCaster;						//影を落とすか？
	bool						m_isShadowMapReceiver;						//影を落とされるか？
	ShaderTechnique				m_shaderTechnique[enShaderTechniqueNum];	//シェーダーテクニックの配列
	EnSkinModelShaderTechnique	m_currentShaderTechnique;					//現在のシェーダーテクニック
	const Texture*				m_pNormalMap;								//法線マップ
	const Texture*				m_pSpecularMap;								//スペキュラマップ
	bool						m_isHasNormalMap;							//法線マップを持っているか？
	bool						m_isHasSpecularMap;							//スペキュラマップを持っているか？	
	D3DXMATRIX					m_worldMatrix;								//ワールド行列
	D3DXMATRIX					m_rotationMatrix;							//回転行列
	SkinModelData*				m_pSkinModelData;							//スキンモデルデータ
	ID3DXEffect*				m_pEffect;									//エフェクト
	Animation					m_animation;								//アニメーション
	const Light*				m_pLight;									//ライト
	const Camera*				m_pCamera;									//スペキュラで使うカメラ
	bool						m_isShadowCompesation;						//地面に垂直な部分に落ちる影の補正するか？
	D3DXVECTOR3					m_position;									//モデルの座標
	D3DXVECTOR3					m_scale;									//モデルのスケール
	D3DXQUATERNION				m_rotation;									//モデルの回転
	bool						m_isShadowEntry;							//シャドウマップに登録されているか？
	float						m_ditheringRate;							//ディザリングの透明度
};