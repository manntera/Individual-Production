#pragma once
//毎フレーム記録するゴーストを動かすためのデータ
struct GhostData	
{
	D3DXVECTOR3 position;			//座標
	D3DXQUATERNION rotation;		//回転
	float animationUpdateTime;		//アニメーションの更新時間
	int currentAnimationNum;		//再生しているアニメーションの番号
};

//ゴーストデータのリスト
struct GhostDataList
{
	std::list<GhostData> ghostData;	//データのリスト
	float time;						//スタートからゴールまでのタイム
};