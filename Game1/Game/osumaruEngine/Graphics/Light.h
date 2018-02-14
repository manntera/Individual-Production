#pragma once

class Light
{
public:
	static const int	DIFFUSE_LIGHT_NUM = 4;	//平行光源の数。
public:
	//コンストラクタ
	Light() :
		m_diffuseLightDirection{},
		m_diffuseLightColor{},
		m_ambientLight(0.0f, 0.0f, 0.0f, 0.0f)
	{
		for (int i = 0;i < DIFFUSE_LIGHT_NUM;i++)
		{
			m_diffuseLightColor[i] = { 0.0f, 0.0f, 0.0f, 1.0f };
			m_diffuseLightDirection[i] = { 1.0f, 0.0f, 0.0f, 1.0f };
		}
	}

	//デストラクタ
	~Light()
	{

	}

	//平行光源の方向を取得。
	const D3DXVECTOR4* GetDiffuseLightDirection() const
	{
		return m_diffuseLightDirection;
	}

	//平行光源の色を取得。
	const D3DXVECTOR4* GetDiffuseLightColor() const
	{
		return m_diffuseLightColor;
	}

	/*
	平行光源の方向を設定。
	lightNo		ライトの番号
	dir			方向。
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		m_diffuseLightDirection[lightNo] = dir;
	}


	/*
	平行光源の色を設定
	lightNo		ライトの番号
	color		色
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		m_diffuseLightColor[lightNo] = color;
	}

	/*
	アンビエントライトを設定。
	ambient		色
	*/
	void SetAmbiemtLight(const D3DXVECTOR4& ambient)
	{
		m_ambientLight = ambient;
	}

	//アンビエントライトを取得。
	const D3DXVECTOR4& GetAmbientLight() const
	{
		return m_ambientLight;
	}
private:
	D3DXVECTOR4			m_diffuseLightDirection[DIFFUSE_LIGHT_NUM];		//ディフューズライトの方向
	D3DXVECTOR4			m_diffuseLightColor[DIFFUSE_LIGHT_NUM];			//ディフューズライトの色
	D3DXVECTOR4			m_ambientLight;									//アンビエントの色
};