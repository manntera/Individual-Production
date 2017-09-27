#pragma once
//ゲームクリアシーンクラス

class GameClearScene : public GameObject
{
public:
	//コンストラクタ
	GameClearScene();

	//デストラクタ
	~GameClearScene();

	//初期化関数
	void Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;
private:
	Sprite m_sprite;		//ゲームクリアのスプライト
};