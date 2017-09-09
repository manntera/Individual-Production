#pragma once
#include "Texture.h"

class Primitive
{
public:

	//�R���X�g���N�^
	Primitive();

	//�f�X�g���N�^
	~Primitive();

	//
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
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//���_��`
	int								m_vertexNum;			//���_��
};		