#pragma once
#include "GhostCommon.h"
//ゴーストデータを記録するクラス

class GhostDataListManager : public GameObject
{
private:
	//コンストラクタ
	GhostDataListManager();

	//デストラクタ
	~GhostDataListManager();
public:
	/*
	計測開始する関数
	position	プレイヤーの座標のアドレス
	rotation	プレイヤーの回転のアドレス
	animation	プレイヤーのアニメーション
	*/
	void Start(D3DXVECTOR3* position, D3DXQUATERNION* rotation, Animation* animation);

	/*
	計測終了する関数
	time		ステージをクリアしたタイム
	isClear		クリアしたか？
	*/
	void Finish(float time, bool isClear);

	//更新関数
	void Update()override;

	//ゴーストデータを取得
	std::list<GhostData>& GetGhostData()
	{
		return m_ghostData[m_stageNum].ghostData;
	}

	static GhostDataListManager& GetInstance() 
	{
		static GhostDataListManager ghostDataListManager;
		return ghostDataListManager;
	}
private:
	D3DXVECTOR3*				m_pPosition;		//プレイヤーの座標
	D3DXQUATERNION*				m_pRotation;		//プレイヤーの回転
	Animation*					m_pAnimation;		//プレイヤーのアニメーション
	std::vector<GhostDataList>	m_ghostData;		//ステージ毎のゴーストデータリスト
	std::list<GhostData>		m_substitute;		//ゴーストデータリスト
	int							m_stageNum;			//ステージの番号
	bool						m_isActive;			//アクティブか？
};


static GhostDataListManager& GetGhostDataListManager()
{
	return GhostDataListManager::GetInstance();
}