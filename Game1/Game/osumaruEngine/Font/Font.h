#pragma once


class Font
{
public:
	void Init(char* chara);

	void Draw();
private:
	LPDIRECT3DTEXTURE9 m_pTexture;

};