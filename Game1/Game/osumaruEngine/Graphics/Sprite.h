#pragma once
#include "../common.h"
class Texture;
class Sprite
{
public:

	Sprite();

	~Sprite();

	void Init(char *filePath);

	void Draw();
private:
	LPD3DXSPRITE m_pSprite;			//スプライト
	Texture* m_pTexture;			//テクスチャ
	D3DXVECTOR3 m_position;			//スプライトのウィンドウ上での座標
	D3DXVECTOR3 m_centerPosition;	//スプライトの基点を表す座標

};