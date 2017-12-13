#include "engineStdafx.h"
#include "RigidBodyDraw.h"
#include "../Engine.h"
#include "../Graphics/EffectManager.h"



RigidBodyDraw::RigidBodyDraw()
{
	m_count = 0;
}

RigidBodyDraw::~RigidBodyDraw()
{
	m_primitive.Release();
}

void RigidBodyDraw::Init()
{
	//頂点数1万で空ノバッファを作成
	const int vertexNum = 10000;
	VERTEX_PC  vertexBuffer[vertexNum];
	DWORD indexBuffer[vertexNum];
	memset(vertexBuffer, 0, sizeof(vertexBuffer)); 
	memset(indexBuffer, 0, sizeof(indexBuffer));
	m_primitive.Create(vertex_PC, vertexBuffer, vertexNum, sizeof(VERTEX_PC), indexBuffer, vertexNum, Primitive::enIndex32, Primitive::enTypeLineList);
	m_pEffect = GetEffectManager().LoadEffect("Assets/shader/rigidBodyDraw.fx");
}

void RigidBodyDraw::drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)
{
	//頂点バッファとインデックスバッファにデータを追加
	VERTEX_PC vertex;
	vertex = { from.x(), from.y(), from.z() , color.x(), color.y(), color.z() };
	m_vertexBuffer.push_back(vertex);
	vertex = { to.x(), to.y(), to.z(), color.x(), color.y(), color.z() };
	m_vertexBuffer.push_back(vertex);
	m_indexBuffer.push_back(m_count * 2);
	m_indexBuffer.push_back(m_count * 2 + 1);
	m_count++;
}

void RigidBodyDraw::Draw(D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	if (m_count == 0)
	{
		return;
	}
	//頂点バッファに書き込んでいく
	const int vertexNum = m_count * 2;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = m_primitive.GetVertexBuffer();
	void* pVertex;
	pVertexBuffer->Lock(0, 0, &pVertex, 0);
	int count = 0;
	for (auto& list : m_vertexBuffer)
	{
		*((VERTEX_PC*)pVertex + count) = list;
		count++;
	}
	pVertexBuffer->Unlock();
	//インデックスバッファに書き込んでいく
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = m_primitive.GetIndexBuffer();
	void* pIndex;
	pIndexBuffer->Lock(0, 0, &pIndex, 0);
	count = 0;
	for (auto& list : m_indexBuffer)
	{
		*((DWORD*)pIndex + count) = list;
		count++;
	}
	pIndexBuffer->Unlock();

	//描画
	LPDIRECT3DDEVICE9 pD3DDevice = GetEngine().GetDevice();
	DWORD cullmodeBackup;
	D3DXMATRIX viewProjection;
	D3DXMatrixIdentity(&viewProjection);
	D3DXMatrixMultiply(&viewProjection, &viewMatrix, &projectionMatrix);

	//描画
	m_pEffect->SetTechnique("RigidBodyDraw");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	m_pEffect->SetMatrix("g_viewProjectionMatrix", &viewProjection);
	m_pEffect->CommitChanges();
	pD3DDevice->SetVertexDeclaration(m_primitive.GetVertexDecaration());
	pD3DDevice->SetStreamSource(0, m_primitive.GetVertexBuffer(), 0, sizeof(VERTEX_PC));
	pD3DDevice->SetIndices(m_primitive.GetIndexBuffer());
	pD3DDevice->DrawIndexedPrimitive(m_primitive.GetPrimitiveType(), 0, 0, vertexNum, 0, m_count);
	m_pEffect->EndPass();
	m_pEffect->End();

	//毎フレームインデックスバッファと頂点バッファをリセット
	m_count = 0;
	m_vertexBuffer.clear();
	m_indexBuffer.clear();
}