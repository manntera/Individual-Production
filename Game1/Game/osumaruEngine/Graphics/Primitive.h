#pragma once
#include "Texture.h"


class Primitive : Uncopyable
{
public:
	enum EnFormatIndex
	{
		enIndex16,
		enIndex32,
	};

	enum EnPrimitiveType
	{
		enTypeLineList,
		enTypeTriangleStrip,
		enTypeTriangleList,
	};

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
	indexFormat			�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
	primitiveType		�v���~�e�B�u�̎��
	*/
	void Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum,  int vertexStride, void *indexBuffer, int indexNum, EnFormatIndex indexFormat, EnPrimitiveType primitivetype );

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

	//���_��`���擾
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDecaration()
	{
		return m_pVertexDecaration;
	}

	int GetPolygonNum()
	{
		return m_polygonNum;
	}

	int GetVertexStride()
	{
		return m_vertexStride;
	}

	D3DPRIMITIVETYPE GetPrimitiveType()
	{
		return m_primitiveType;
	}

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//���_��`
	int								m_vertexNum;			//���_��
	D3DPRIMITIVETYPE				m_primitiveType;
	int								m_polygonNum;
	int								m_vertexStride;
};		