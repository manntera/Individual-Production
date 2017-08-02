#pragma once
#include"../../common.h"

struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16	CombinedTransformationMatrix;		//çáê¨çœÇ›çsóÒÅB
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*		ppTextures;
	LPD3DXMESH				pOrgMesh;
	LPD3DXATTRIBUTERANGE	pAttributeTable;
	DWORD					NumAttributeGroups;
	DWORD					NumInfi;
	LPD3DXBUFFER			pBoneCombinationBuf;
	D3DXMATRIX**			ppBoneMatrixPtrs;
	D3DXMATRIX*				pBoneOffsetMatrices;
	DWORD					NumPaletteEntries;
	bool					UseSoftwareVP;
	DWORD					iAttributeSW;
};

class Animation;

class SkinModelData
{
public:

private:
	LPD3DXFRAME					frameRoot;
	ID3DXAnimationController*	pAnimController;
};