#pragma once

//スキンモデルデータ

struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16	CombinedTransformationMatrix;		//合成済み行列。
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*		ppTextures;
	LPD3DXMESH				pOrgMesh;
	LPD3DXATTRIBUTERANGE	pAttributeTable;
	DWORD					NumAttributeGroups;
	DWORD					NumInfi;
	LPD3DXBUFFER			pBoneCombinationBuf;
	D3DXMATRIX**			ppBoneMatrixPtrs;
	D3DXMATRIX*				pBoneOffsetMatrices;
	DWORD					NumPaletteEntries;
	bool					UseSoftwareVP;
	DWORD					iAttributeSW;
};

class Animation;

class SkinModelData : Uncopyable
{
public:
	//コンストラクタ
	SkinModelData();

	//デストラクタ
	~SkinModelData();

	/*
	モデルデータをロード
	filepath	ファイルパス
	anim		アニメーション付きモデルデータの場合アニメーションクラスも構築されます。
	*/
	void LoadModelData(const char* filePath, Animation* anim);

	//リリース関数
	void Release();

	//フレームルートを取得
	const LPD3DXFRAME GetFrameRoot() const
	{
		return m_frameRoot;
	}
	//ボーン行列を更新
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

	//一番最初に見つかったオリジナルメッシュを取得
	const LPD3DXMESH GetOrgMeshFirst() const;

	//ルートのボーンを取得
	const D3DXMATRIX* GetRootBoneWorldMatrix() const
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)m_frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}
	/*
	ボーンを検索してワールド行列を取得
	boneName	ボーンの名前
	return		ボーンのワールド行列
	*/
	const D3DXMATRIX* GetFindBoneWorldMatrix(char *boneName) const;

	/*
	モデルデータのクローンを作る
	modelData	オリジナルのmodelData
	anim		クローンのアニメーション
	*/
	void CloneModelData(const SkinModelData& modelData, Animation* anim);
private:
	/*
	フレームのクローンを作る(再帰関数)
	destFrame	クローン側のフレーム
	srcFrame	オリジナル側のフレーム
	*/
	void CloneSkelton(LPD3DXFRAME& destFrame, LPD3DXFRAME srcFrame);

	//一番最初に見つかったオリジナルメッシュを取得。
	const LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) const;

	/*
	ボーンを検索してワールド行列を取得(再帰関数)
	frame		ルートフレーム
	boneNmae	ボーンの名前
	return ボーンのワールド行列
	*/
	const D3DXMATRIX* FindBoneWorldMatrix(LPD3DXFRAME frame, char* boneName) const;

	/*
	アニメーションとボーンの対応付け(再帰関数)
	frame	ルートフレーム
	animCtr	アニメーションンコントローラー
	*/
	void SetOutputAnimationRegist(LPD3DXFRAME frame, LPD3DXANIMATIONCONTROLLER animCtr);

	/*
	クローン用のモデルの削除関数
	frame	ルートフレーム
	*/
	void DeleteCloneSkelton(LPD3DXFRAME frame);

private:
	LPD3DXFRAME					m_frameRoot;			//フレームルート。
	ID3DXAnimationController*	m_pAnimController;		//アニメーションコントローラ。
	bool						m_isClone;				//クローンか？
};