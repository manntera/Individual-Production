#pragma once
//��肩���̃N���X
//�t�H���g��\�����悤�Ƃ��ēr���ł�߂����

class Font
{
public:
	void Init(char* chara);

	void Draw();
private:
	LPDIRECT3DTEXTURE9 m_pTexture;

};