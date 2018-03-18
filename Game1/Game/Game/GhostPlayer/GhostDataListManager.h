#pragma once
#include "GhostCommon.h"
//ゴーストデータを記録し管理するクラス

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
	void Start(const D3DXVECTOR3* position, const D3DXQUATERNION* rotation, const Animation* animation);

	/*
	計測終了する関数
	time		ステージをクリアしたタイム
	isClear		クリアしたか？
	*/
	void Finish(float time, bool isClear);

	//更新関数
	void Update()override;

	//ゴーストデータを取得
	const std::list<GhostData>& GetGhostData() const
	{
		return m_ghostData[m_stageNum].ghostData;
	}

	//自身のインスタンスを取得
	static GhostDataListManager& GetInstance() 
	{
		static GhostDataListManager ghostDataListManager;
		return ghostDataListManager;
	}

	//ゴーストデータの読み込み
	void GhostDataRead();

	//ゴーストデータのセーブ
	void GhostDataSave();


	//アクティブかのフラグを設定する。
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}
private:
	const D3DXVECTOR3*			m_pPosition;		//プレイヤーの座標
	const D3DXQUATERNION*		m_pRotation;		//プレイヤーの回転
	const Animation*			m_pAnimation;		//プレイヤーのアニメーション
	std::vector<GhostDataList>	m_ghostData;		//ステージ毎のゴーストデータリスト
	std::list<GhostData>		m_substitute;		//ゴーストデータリスト
	int							m_stageNum;			//ステージの番号
	bool						m_isActive;			//アクティブか？
};


//ゴーストデータリストマネージャーを取得。
static GhostDataListManager& GetGhostDataListManager()
{
	return GhostDataListManager::GetInstance();
}