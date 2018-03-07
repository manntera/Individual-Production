#pragma once
//作りかけのクラス
//フォントを表示しようとして途中でやめたやつ

class Font
{
public:
	void Init(char* chara);

	void Draw();
private:
	LPDIRECT3DTEXTURE9 m_pTexture;

};