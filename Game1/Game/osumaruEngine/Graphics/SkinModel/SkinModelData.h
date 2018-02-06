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

class SkinModelData : Uncopyable
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
	const LPD3DXFRAME GetFrameRoot() const
	{
		return m_frameRoot;
	}
	//�{�[���s����X�V
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾
	const LPD3DXMESH GetOrgMeshFirst() const;

	//���[�g�̃{�[�����擾
	const D3DXMATRIX* GetRootBoneWorldMatrix() const
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)m_frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}
	/*
	�{�[�����������ă��[���h�s����擾
	boneName	�{�[���̖��O
	return		�{�[���̃��[���h�s��
	*/
	const D3DXMATRIX* GetFindBoneWorldMatrix(char *boneName) const;

	/*
	���f���f�[�^�̃N���[�������
	modelData	�I���W�i����modelData
	anim		�N���[���̃A�j���[�V����
	*/
	void CloneModelData(const SkinModelData& modelData, Animation* anim);
private:
	/*
	�t���[���̃N���[�������(�ċA�֐�)
	destFrame	�N���[�����̃t���[��
	srcFrame	�I���W�i�����̃t���[��
	*/
	void CloneSkelton(LPD3DXFRAME& destFrame, LPD3DXFRAME srcFrame);

	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾�B
	const LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame) const;

	/*
	�{�[�����������ă��[���h�s����擾(�ċA�֐�)
	frame		���[�g�t���[��
	boneNmae	�{�[���̖��O
	return �{�[���̃��[���h�s��
	*/
	const D3DXMATRIX* FindBoneWorldMatrix(LPD3DXFRAME frame, char* boneName) const;

	/*
	�A�j���[�V�����ƃ{�[���̑Ή��t��(�ċA�֐�)
	frame	���[�g�t���[��
	animCtr	�A�j���[�V�������R���g���[���[
	*/
	void SetOutputAnimationRegist(LPD3DXFRAME frame, LPD3DXANIMATIONCONTROLLER animCtr);

	/*
	�N���[���p�̃��f���̍폜�֐�
	frame	���[�g�t���[��
	*/
	void DeleteCloneSkelton(LPD3DXFRAME frame);

private:
	LPD3DXFRAME					m_frameRoot;			//�t���[�����[�g�B
	ID3DXAnimationController*	m_pAnimController;		//�A�j���[�V�����R���g���[���B
	bool						m_isClone;				//�N���[�����H
};