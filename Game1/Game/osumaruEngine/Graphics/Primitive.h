#pragma once
#include "Texture.h"

class Primitive
{
public:
	void Create(D3DVERTEXELEMENT9 *vertexLayout, void *vertexBuffer, int vertexNum,  int vertexStride, WORD *indexBuffer, int indexNum);

	//���_�o�b�t�@�̃Q�b�^�[
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}

	//�C���f�b�N�X�o�b�t�@�̃Q�b�^�[
	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	//���_���̃Q�b�^�[
	int GetVertexNum()
	{
		return m_vertexNum;
	}
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;
	LPDIRECT3DVERTEXDECLARATION9	m_pVertexDecaration;
	int								m_vertexNum;
};		