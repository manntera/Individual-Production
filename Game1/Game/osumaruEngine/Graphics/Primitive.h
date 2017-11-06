#pragma once
#include "Texture.h"

class Primitive : Uncopyable
{
public:

	//�R���X�g���N�^
	Primitive();

	//�f�X�g���N�^
	~Primitive();

	/*
	�v���~�e�B�u�����֐�
	vertexLayout		���_��`�̃��C�A�E�g
	vertexBuffer		���_�o�b�t�@
	vertexNum			���_��
	vertexStride		���_�f�[�^�̃T�C�Y
	indexBuffer			�C���f�b�N�X�o�b�t�@
	indexNum			�C���f�b�N�X��
	*/
	void Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum,  int vertexStride, WORD *indexBuffer, int indexNum);

	//���_�o�b�t�@���擾�B
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}

	//�C���f�b�N�X�o�b�t�@���擾�B
	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	//���_�����擾�B
	int GetVertexNum()
	{
		return m_vertexNum;
	}
	//�����[�X
	void Release();


	LPDIRECT3DVERTEXDECLARATION9 GetVertexDecaration()
	{
		return m_pVertexDecaration;
	}
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//���_��`
	int								m_vertexNum;			//���_��
};		