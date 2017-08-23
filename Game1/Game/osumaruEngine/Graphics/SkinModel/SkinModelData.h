//#pragma once
//#include"../../common.h"
//
//struct D3DXFRAME_DERIVED : public D3DXFRAME
//{
//	D3DXMATRIXA16	CombinedTransformationMatrix;		//合成済み行列。
//};
//
//struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
//{
//	LPDIRECT3DTEXTURE9*		ppTextures;
//	LPD3DXMESH				pOrgMesh;
//	LPD3DXATTRIBUTERANGE	pAttributeTable;
//	DWORD					NumAttributeGroups;
//	DWORD					NumInfi;
//	LPD3DXBUFFER			pBoneCombinationBuf;
//	D3DXMATRIX**			ppBoneMatrixPtrs;
//	D3DXMATRIX*				pBoneOffsetMatrices;
//	DWORD					NumPaletteEntries;
//	bool					UseSoftwareVP;
//	DWORD					iAttributeSW;
//};
//
//class Animation;
//
//class SkinModelData
//{
//public:
//
//	SkinModelData();
//
//	~SkinModelData();
//
//	/*
//	モデルデータをロード
//	filepath	ファイルパス
//	anim		アニメーション付きモデルデータの場合アニメーションクラスも構築されます。
//	*/
//	void LoadModelData(const char* filePath, Animation* anim);
//
//	void Release();
//
//	LPD3DXFRAME GetFrameRoot()
//	{
//		return frameRoot;
//	}
//	//ボーン行列を更新
//	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);
//
//	//一番最初に見つかったオリジナルメッシュを取得
//	LPD3DXMESH GetOrgMeshFirst();
//
//	//ルートのボーンを取得
//	D3DXMATRIX* GetRootBoneWorldMatrix()
//	{
//		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)frameRoot;
//		return &frameDer->CombinedTransformationMatrix;
//	}
//private:
//	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame);
//private:
//	LPD3DXFRAME					frameRoot;
//	ID3DXAnimationController*	pAnimController;
//};