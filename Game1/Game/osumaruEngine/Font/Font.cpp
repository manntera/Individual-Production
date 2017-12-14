#include "engineStdafx.h"
#include "Font.h"
#include "../Engine.h"

void Font::Init(char* chara)
{
	GLYPHMETRICS glyph;
	MAT2 mat = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };
	HFONT font;
	font = CreateFont(
		24,
		0,
		0,
		0,
		FW_DONTCARE,
		false,
		false,
		false,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		NULL);
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, font);
	char* c= "a";
	UINT code;
	if (IsDBCSLeadByte(*c))
	{
		code = (BYTE)c[0] << 8 | (BYTE)c[1];
	}
	else
	{
		code = c[0];
	}
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &glyph, 0, NULL, &mat);
	BYTE *pByte = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &glyph, size, pByte, &mat);

	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	device->CreateTexture(
		glyph.gmBlackBoxX,
		glyph.gmBlackBoxY,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pTexture,
		NULL);
	D3DLOCKED_RECT lockedRect;
	m_pTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD);
	FillMemory(lockedRect.pBits, lockedRect.Pitch * glyph.gmBlackBoxY, 0);
	for (int y = 0; y < glyph.gmBlackBoxY; y++)
	{
		for (int x = 0; x < glyph.gmBlackBoxX; x++)
		{
			DWORD Trans;
		}
	}


	SelectObject(hdc, oldFont);
	DeleteObject(font);
	ReleaseDC(NULL, hdc);
	delete[] pByte;
}