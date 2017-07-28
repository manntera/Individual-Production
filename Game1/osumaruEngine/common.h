#pragma once
class EffectManager;
int MakeHash(const char* string);

#include <d3d9.h>
#include <d3dx9effect.h>
#include <vector>
#include <map>

#include <stdio.h>
#include <string.h>

extern LPDIRECT3D9			g_pD3D;
extern LPDIRECT3DDEVICE9	g_pD3DDevice;
extern EffectManager*		g_effectManager;