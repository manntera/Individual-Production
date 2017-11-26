#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/VertexCommon.h"
//剛体を表示するクラス

class RigidBodyDraw : public btIDebugDraw
{
public:
	//コンストラクタ
	RigidBodyDraw();

	//デストラクタ
	~RigidBodyDraw();

	//初期化関数
	void Init();

	/*
	頂点を追加する関数
	from	1個目の頂点
	to		2個目の頂点
	color	プリミティブの色
	*/
	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)override;

	/*
	描画関数
	viewMatrix			カメラのビュー行列
	projectionMatrix	カメラの射影行列
	*/
	void Draw(D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);

	//よくわかってない
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

	//よくわかってない
	void reportErrorWarning(const char* warningString) {}

	//よくわかってない
	void draw3dText(const btVector3& location, const char* textString) {}

	//よくわかってない
	void setDebugMode(int debugMode) {}

	//よくわかってない
	int getDebugMode() const
	{
		return 0;
	}

private:
	std::list<WORD> m_indexBuffer;			//インデックスバッファ
	std::list<VERTEX_PC> m_vertexBuffer;	//頂点バッファ
	Primitive		m_primitive;			//プリミティブ
	int				m_count;				//プリミティブの数
	LPD3DXEFFECT	m_pEffect;				//エフェクト

};