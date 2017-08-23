//#pragma once
//#include "Animation.h"
//
//class SkinModelData;
//class RenderContext;
//class Light;
//
//class SkinModel
//{
//public:
//
//	SkinModel();
//
//	~SkinModel();
//
//	//初期化
//	void Init(SkinModelData* modelData);
//
//	void Draw(D3DXMATRIX* viewmatrix, D3DXMATRIX* projMatrix);
//
//	/*
//	ワールド行列を更新。
//	trans	平行移動
//	rot		回転
//	scale	拡大
//	*/
//	void UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);
//
//	/*
//	ライトを設定
//	*/
//	void SetLight(Light *light)
//	{
//		this->light = = light;
//	}
//	/*
//	オリジナルメッシュの先頭を取得する
//	*/
//
//private:
//	D3DXMATRIX		worldMatrix;				//ワールド行列
//	D3DXMATRIX		rotationMatrix;				//回転行列
//	SkinModelData*	skinModelData;				//スキンモデルデータ
//	ID3DXEffect*	pEffect;					//エフェクト
//	Animation		animation;					//アニメーション
//	Light*			light;						//ライト
//};