//#pragma once
//#include"../../common.h"
//
//struct D3DXFRAME_DERIVED : public D3DXFRAME
//{
//	D3DXMATRIXA16	CombinedTransformationMatrix;		//�����ςݍs��B
//};
//
//struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
//{
//	LPDIRECT3DTEXTURE9*		ppTextures;
//	LPD3DXMESH				pOrgMesh;
//	LPD3DXATTRIBUTERANGE	pAttributeTable;
//	DWORD					NumAttributeGroups;
//	DWORD					NumInfi;
//	LPD3DXBUFFER			pBoneCombinationBuf;
//	D3DXMATRIX**			ppBoneMatrixPtrs;
//	D3DXMATRIX*				pBoneOffsetMatrices;
//	DWORD					NumPaletteEntries;
//	bool					UseSoftwareVP;
//	DWORD					iAttributeSW;
//};
//
//class Animation;
//
//class SkinModelData
//{
//public:
//
//	SkinModelData();
//
//	~SkinModelData();
//
//	/*
//	���f���f�[�^�����[�h
//	filepath	�t�@�C���p�X
//	anim		�A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�j���[�V�����N���X���\�z����܂��B
//	*/
//	void LoadModelData(const char* filePath, Animation* anim);
//
//	void Release();
//
//	LPD3DXFRAME GetFrameRoot()
//	{
//		return frameRoot;
//	}
//	//�{�[���s����X�V
//	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);
//
//	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾
//	LPD3DXMESH GetOrgMeshFirst();
//
//	//���[�g�̃{�[�����擾
//	D3DXMATRIX* GetRootBoneWorldMatrix()
//	{
//		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)frameRoot;
//		return &frameDer->CombinedTransformationMatrix;
//	}
//private:
//	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame);
//private:
//	LPD3DXFRAME					frameRoot;
//	ID3DXAnimationController*	pAnimController;
//};