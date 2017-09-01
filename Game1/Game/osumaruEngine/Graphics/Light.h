#pragma once

class Light
{
public:
	static const int	DIFFUSE_LIGHT_NUM = 4;	//平行光源の数。
public:
	Light()
	{
		memset(this, 0, sizeof(Light));
	}
	~Light()
	{

	}

	//平行光源の方向を取得。
	const D3DXVECTOR4* GetDiffuseLightDirection() const
	{
		return diffuseLightDirection;
	}

	//平行光源の色を取得。
	const D3DXVECTOR4* GetDiffuseLightColor() const
	{
		return diffuseLightColor;
	}

	/*
	平行光源の方向を設定。
	lightNo		ライトの番号
	dir			方向。
	*/
	void SetDiffuseLightDirection(int lightNo, const D3DXVECTOR4& dir)
	{
		diffuseLightDirection[lightNo] = dir;
	}


	/*
	平行光源の色を設定
	lightNo		ライトの番号
	color		色
	*/
	void SetDiffuseLightColor(int lightNo, const D3DXVECTOR4& color)
	{
		diffuseLightColor[lightNo] = color;
	}
	void SetAmbiemtLight(const D3DXVECTOR4& ambient)
	{
		ambientLight = ambient;
	}

	const D3DXVECTOR4& GetAmbientLight() const
	{
		return ambientLight;
	}
private:
	D3DXVECTOR4			diffuseLightDirection[DIFFUSE_LIGHT_NUM];
	D3DXVECTOR4			diffuseLightColor[DIFFUSE_LIGHT_NUM];
	D3DXVECTOR4			ambientLight;
};