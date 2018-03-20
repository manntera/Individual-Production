#pragma once

static const int SHADOWMAP_NUM = 3;

float4  CalcShadowMap(sampler shadowMap, float4 position)
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//ライトカメラから見た座標をもとにシャドウマップのuvを計算
	float2 uv = position.xy / position.w;
	if (uv.x >= -1.0f && uv.x <= 1.0f && uv.y >= -1.0f && uv.y <= 1.0f)
	{
		//－1.0f～1.0fのスクリーン座標から0.0f～1.0fのテクスチャのuv座標に変換
		uv += 1.0f;
		uv *= 0.5f;
		uv.y = 1.0f - uv.y;
		float4 shadow = tex2D(shadowMap, uv);
		//ライトカメラから見た深度値を計算
		float shadowDepth = position.z / position.w;
		shadowDepth = min(1.0f, shadowDepth);
		//シャドウマップの深度値と比較してシャドウマップのより奥にあれば影を落とす
		if (shadow.x < shadowDepth - 0.00005f)
		{
			color = float4(0.7f, 0.7f, 0.7f, 1.0f);
		}
	}
	return color;
}