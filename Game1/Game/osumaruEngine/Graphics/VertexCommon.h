#pragma once
#include "d3d9types.h"

//頂点ストライド
struct VERTEX_PT
{
	float pos[4];
	float uv[2];
};

static D3DVERTEXELEMENT9 vertex_PT[] =
{
	//ストリーム番号	先頭からのオフセット	データ型				よくわからない			セマンティクス(データの使用方法)	よくわからない
	{ 0,				0,						D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_POSITION,				0},
	{ 0,				16,						D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD,				0},
};