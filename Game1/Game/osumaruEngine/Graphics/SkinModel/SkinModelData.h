#pragma once

//�X�L�����f���f�[�^

struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16	CombinedTransformationMatrix;		//�����ςݍs��B
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
	//�R���X�g���N�^
	SkinModelData();

	//�f�X�g���N�^
	~SkinModelData();

	/*
	���f���f�[�^�����[�h
	filepath	�t�@�C���p�X
	anim		�A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�j���[�V�����N���X���\�z����܂��B
	*/
	void LoadModelData(const char* filePath, Animation* anim);

	//�����[�X�֐�
	void Release();


	//�t���[�����[�g���擾
	LPD3DXFRAME GetFrameRoot()
	{
		return m_frameRoot;
	}
	//�{�[���s����X�V
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾
	LPD3DXMESH GetOrgMeshFirst();

	//���[�g�̃{�[�����擾
	D3DXMATRIX* GetRootBoneWorldMatrix()
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)m_frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}
	D3DXMATRIX* GetFindBoneWorldMatrix(char *boneName);
private:
	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾�B
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame);

	D3DXMATRIX* FindBoneWorldMatrix(LPD3DXFRAME frame, char* boneName);
private:
	LPD3DXFRAME					m_frameRoot;			//�t���[�����[�g�B
	ID3DXAnimationController*	m_pAnimController;	//�A�j���[�V�����R���g���[���B
};