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
	const LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() const
	{
		return m_pVertexBuffer;
	}

	//�C���f�b�N�X�o�b�t�@���擾�B
	const LPDIRECT3DINDEXBUFFER9 GetIndexBuffer() const
	{
		return m_pIndexBuffer;
	}
	//���_�����擾�B
	int GetVertexNum() const
	{
		return m_vertexNum;
	}
	//�����[�X
	void Release();

	//���_��`���擾
	const LPDIRECT3DVERTEXDECLARATION9 GetVertexDecaration() const
	{
		return m_pVertexDecaration;
	}

	//�|���S�������擾
	int GetPolygonNum() const
	{
		return m_polygonNum;
	}

	//���_�X�g���C�h���擾
	int GetVertexStride() const
	{
		return m_vertexStride;
	}

	//�v���~�e�B�u�^�C�v���擾
	D3DPRIMITIVETYPE GetPrimitiveType() const
	{
		return m_primitiveType;
	}

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;		//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;			//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;	//���_��`
	int								m_vertexNum;			//���_��
	D3DPRIMITIVETYPE				m_primitiveType;		//�v���~�e�B�u�̎��
	int								m_polygonNum;			//�|���S����
	int								m_vertexStride;			//���_�X�g���C�h
};		