#include "engineStdafx.h"
#include "MeshCollider.h"
#include "../../Graphics/SkinModel/SkinModel.h"

MeshCollider::MeshCollider()
{
	m_stridingMeshInterface = nullptr;
	m_meshShape = nullptr;
}

MeshCollider::~MeshCollider()
{
	for (auto& vb : m_vertexBufferArray)
	{
		delete vb;
	}
	for (auto& ib : m_indexBufferArray)
	{
		delete ib;
	}
	delete m_stridingMeshInterface;
	delete m_meshShape;
}

void MeshCollider::CreateFromSkinModel(SkinModel* model, const D3DXMATRIX* offsetMatrix)
{
	m_stridingMeshInterface = new btTriangleIndexVertexArray;
	LPD3DXMESH mesh = model->GetOrgMeshFirst();
	if (mesh != NULL)
	{
		{
			//頂点ストライドを取得
			DWORD stride = D3DXGetFVFVertexSize(mesh->GetFVF());
			//頂点バッファを取得。
			LPDIRECT3DVERTEXBUFFER9 vb;
			mesh->GetVertexBuffer(&vb);
			//頂点バッファの定義を取得
			D3DVERTEXBUFFER_DESC desc;
			vb->GetDesc(&desc);
			//頂点バッファをロックする。
			D3DXVECTOR3* pos;
			vb->Lock(0, 0, (void**)&pos, D3DLOCK_READONLY);
			VertexBuffer* vertexBuffer = new VertexBuffer;
			int numVertex = mesh->GetNumVertices();
			for (int v = 0; v < numVertex; v++)
			{
				D3DXVECTOR3 posTmp = *pos;
				if (offsetMatrix)
				{
					D3DXVec3TransformCoord(&posTmp, pos, offsetMatrix);
				}
				vertexBuffer->push_back(posTmp);
				char* p = (char*)pos;
				p += stride;
				pos = (D3DXVECTOR3*)p;
			}
			vb->Unlock();
			vb->Release();
			m_vertexBufferArray.push_back(vertexBuffer);
		}
		{
			//続いてインデックスバッファを作成
			LPDIRECT3DINDEXBUFFER9 ib;
			mesh->GetIndexBuffer(&ib);
			//インデックスバッファの定義を取得
			D3DINDEXBUFFER_DESC desc;
			ib->GetDesc(&desc);
			int stride = 0;
			if (desc.Format == D3DFMT_INDEX16)
			{
				//インデックスが16bit
				stride = 2;
			}
			else if (desc.Format == D3DFMT_INDEX32)
			{
				//インデクスが32bit
				stride = 4;
			}

			char* p;
			HRESULT hr = ib->Lock(0, 0, (void**)&p, D3DLOCK_READONLY);
			IndexBuffer* indexBuffer = new IndexBuffer;
			for (int i = 0; i < (int)desc.Size / stride; i++)
			{
				unsigned int index;
				if (desc.Format == D3DFMT_INDEX16)
				{
					unsigned short* pIndex = (unsigned short*)p;
					index = (unsigned int)*pIndex;
				}
				else
				{
					unsigned int* pIndex = (unsigned int*)p;
					index = *pIndex;
				}
				indexBuffer->push_back(index);
				p += stride;
			}
			ib->Unlock();
			ib->Release();
			m_indexBufferArray.push_back(indexBuffer);
		}
		//インデックスメッシュを作成
		btIndexedMesh indexedMesh;
		IndexBuffer* ib = m_indexBufferArray.back();
		VertexBuffer* vb = m_vertexBufferArray.back();
		//indexedMesh.m_numTriangles = (int)ib->size / 3;
		indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib->front());
		indexedMesh.m_triangleIndexStride = 12;
		indexedMesh.m_numVertices = (unsigned int)vb->size();
		indexedMesh.m_vertexBase = (unsigned char*)(&vb->front());
		indexedMesh.m_vertexStride = sizeof(D3DXVECTOR3);
		m_stridingMeshInterface->addIndexedMesh(indexedMesh);
	}
	m_meshShape = new btBvhTriangleMeshShape(m_stridingMeshInterface, true);
}


