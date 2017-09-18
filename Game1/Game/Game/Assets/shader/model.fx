//スキンモデルシェーダー(4ボーンスキニング)

#include "LightingFunction.h"

//スキン行列
#define MAX_MATRICES 26
float4x3	g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4	g_mViewProj	: VIEWPROJECTION;
float		g_numBone;			//骨の数。

float4x4	g_worldMatrix;			//ワールド行列
float4x4	g_rotationMatrix;		//回転行列。
float4x4	g_viewMatrixRotInv;		//カメラの回転行列
float3		g_cameraPos;			//スペキュラ用のカメラ視点
float4x4	g_invWorldMatrix;
float4x4	g_lightViewMatrix;
float4x4	g_lightProjMatrix;
float4x4	g_lightViewProjMatrix;
bool	g_flg;

bool	g_isShadowMapCaster;
bool	g_isShadowMapReceiver;

bool	g_isHasNormalMap;			//法線マップ保持している？
bool	g_isHasSpecularMap;			//法線マップ保持している？
texture g_diffuseTexture;			//ディフューズテクスチャ
sampler g_diffuseTextureSampler =
sampler_state
{
	Texture = <g_diffuseTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//法線マップ
texture g_normalTexture;		//法線マップ
sampler g_normalMapSampler =
sampler_state
{
	Texture = <g_normalTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//スペキュラマップ
texture g_specularTexture;		//スペキュラマップ
sampler g_specularMapSampler =
sampler_state
{
	Texture = <g_specularTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//シャドウマップ
texture g_shadowMapTexture;		//スペキュラマップ
sampler g_shadowMapSampler =
sampler_state
{
	Texture = <g_shadowMapTexture>;
	//MipFilter = NONE;
	//MinFilter = NONE;
	//MagFilter = NONE;
	//AddressU = Wrap;
	//AddressV = Wrap;
};

//入力頂点
struct VS_INPUT
{
	float4 Pos			: POSITION;
	float4 BlendWeights	: BLENDWEIGHT;
	float4 BlendIndices	: BLENDINDICES;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;		//接ベクトル
	float3 Tex0			: TEXCOORD0;
};

//出力頂点。
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float3 Normal		: NORMAL;
	float2 Tex0			: TEXCOORD0;
	float3 Tangent		: TEXCOORD1;	//接ベクトル
	float4 LightDir		: TEXCOORD2;
	float3 WorldPos		: TEXCOORD3; 
	float4 LightPos		: TEXCOORD4;
};

/*
ワールド座標とワールド法線をスキン行列から計算する。
In		入力頂点
Pos		ワールド座標の格納先。
Normal	ワールド法線の格納先。
Tangent	ワールド接ベクトルの格納先。
*/
void CalcWorldPosAndNormalFromSkinMatrix(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent)
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	//ブレンドレート。
	float	BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int		IndexArray[4] = (int[4])IndexVector;
	float LastWeight = 0.0f;
	for (int iBone = 0; iBone < g_numBone - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
	Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
	Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
}

/*
ワールド座標とワールド法線を計算。
In		入力頂点。
Pos		ワールド座標の格納先。
Normal	ワールド法線の格納先。
Tangent	ワールド接ベクトルの格納先。
*/
void CalcWorldPosAndNormal(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent)
{
	Pos = mul(In.Pos, g_worldMatrix);
	Normal = mul(In.Normal, g_rotationMatrix);
	Tangent = mul(In.Tangent, g_rotationMatrix);
}

/*
頂点シェーダー
In		入力頂点
hasSkin	スキンあり？
*/
VS_OUTPUT VSMain(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin)
	{
		//スキン有り
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent);
	}
	else
	{
		//スキン無し
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent);
	}
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	float3 biNormal;
	biNormal = cross(Normal, Tangent);
	biNormal = normalize(biNormal);
	Out.Normal = normalize(Normal);
	Out.Tangent = normalize(Tangent);
	float4x4 mat = {
		float4(Out.Tangent, 0.0f),
		float4(biNormal, 0.0f),
		float4(Out.Normal, 0.0f),
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	mat = transpose(mat);
	float4 lightDir = -g_light.diffuseLightDir[0];
	lightDir = mul(lightDir, g_invWorldMatrix);
	Out.LightDir = mul(lightDir, mat);
	Out.LightDir.xyz = normalize(Out.LightDir.xyz);
	Out.Tex0 = In.Tex0;
	Out.WorldPos = Pos.xyz;
	Out.LightPos = mul(float4(Pos.xyz, 1.0f), g_lightViewProjMatrix);
	return Out;
}

//ピクセルシェーダー
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;
	float4 lig = DiffuseLight(normal);
	//if (g_isHasNormalMap)
	//{
	//	float3 normalColor = tex2D(g_normalMapSampler, In.Tex0);
	//	float3 normalVector = normalColor * 2 - 1.0f;
	//	normalVector = normalize(normalVector);

	//	float3 light = max(0, dot(In.LightDir.xyz, normalVector)) * g_light.diffuseLightColor[0].xyz;
	//	lig.xyz *= light;
	//	lig += g_light.ambient;
	//	lig.w = 1.0f;
	//}
	//if (g_isHasSpecularMap)
	//{
	//	float3 textureNormal = In.Normal;
	//	textureNormal = normalize(textureNormal);
	//	float3 gaze = In.WorldPos - g_cameraPos;
	//	textureNormal *= dot(textureNormal, -gaze);
	//	gaze += textureNormal * 2.0f;
	//	gaze = normalize(gaze);
	//	float3 lightDir = -g_light.diffuseLightDir[0].xyz;
	//	lightDir = normalize(lightDir);
	//	float3 specColor = tex2D(g_specularMapSampler, In.Tex0).xyz;
	//	lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[0].xyz * length(specColor) * 3.0f;
	//	lig.w = 1.0f;
	//}
	if (g_isShadowMapReceiver)
	{
		float2 uv = In.LightPos.xy / In.LightPos.w;
		uv += 1.0f;
		uv /= 2.0f;
		uv.y = 1.0f - uv.y;
		lig *= tex2D(g_shadowMapSampler, uv);
	}
	color *= lig;
	return color;
}

/*
頂点シェーダー
In		入力頂点
hasSkin	スキンあり？
*/
VS_OUTPUT ShadowMapVSMain(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin)
	{
		//スキン有り
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent);
	}
	else
	{
		//スキン無し
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent);
	}
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_lightViewProjMatrix);
	return Out;
}


float4 ShadowMapPSMain(VS_OUTPUT In) : COLOR
{
	return float4(0.7f, 0.7f, 0.7f, 1.0f);
}


//スキンありモデル用のテクニック。
technique SkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//スキンなしモデル用テクニック。
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

technique SkinShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 ShadowMapVSMain(true);
		PixelShader = compile ps_3_0 ShadowMapPSMain();
	}
}

technique NoSkinShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 ShadowMapVSMain(false);
		PixelShader = compile ps_3_0 ShadowMapPSMain();
	}
}
