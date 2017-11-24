#pragma once
#include "d3d9types.h"

//���_�X�g���C�h
struct VERTEX_PT
{
	float pos[4];
	float uv[2];
};

static D3DVERTEXELEMENT9 vertex_PT[] =
{
	//�X�g���[���ԍ�	�擪����̃I�t�Z�b�g	�f�[�^�^				�悭�킩��Ȃ�			�Z�}���e�B�N�X(�f�[�^�̎g�p���@)	�悭�킩��Ȃ�
	{ 0,				0,						D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_POSITION,				0},
	{ 0,				16,						D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD,				0},
	D3DDECL_END()
};

struct VERTEX_PC
{
	float pos[4];
	float color[3];
};

static D3DVERTEXELEMENT9 vertex_PC[] =
{
	//�X�g���[���ԍ�	�擪����̃I�t�Z�b�g	�f�[�^�^				�悭�킩��Ȃ�			�Z�}���e�B�N�X(�f�[�^�̎g�p���@)	�悭�킩��Ȃ�
	{ 0,				0,						D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_POSITION,				0 },
	{ 0,				16,						D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_COLOR,					0 },
	D3DDECL_END()
};