//スキンモデルシェーダー(4ボーンスキニング)

#include "LightingFunction.h"
#include "ShadowFunction.h"

//スキン行列
#define MAX_MATRICES 26
float4x3	g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4	g_mViewProj	: VIEWPROJECTION;
float		g_numBone;			//骨の数。

float4x4	g_worldMatrix;			//ワールド行列
float4x4	g_rotationMatrix;		//回転行列。
float4x4	g_viewMatrixRotInv;		//カメラの回転行列
float3		g_cameraPos;			//スペキュラ用のカメラ視点
float3		g_cameraDir;
float4x4	g_invWorldMatrix;
float4x4	g_lightViewProjMatrix[SHADOWMAP_NUM];
int			g_screenWidth;
int			g_screenHeight;
float		g_ditheringRate;



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
texture g_shadowMapTexture1;		//スペキュラマップ
sampler g_shadowMapSampler1 =
sampler_state
{
	Texture = <g_shadowMapTexture1>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//シャドウマップ
texture g_shadowMapTexture2;		//スペキュラマップ
sampler g_shadowMapSampler2 =
sampler_state
{
	Texture = <g_shadowMapTexture2>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//シャドウマップ
texture g_shadowMapTexture3;		//スペキュラマップ
sampler g_shadowMapSampler3 =
sampler_state
{
	Texture = <g_shadowMapTexture3>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//深度マップ
texture g_depthTexture;		//スペキュラマップ
sampler g_depthSampler =
sampler_state
{
	Texture = <g_depthTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
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
	float4 Pos					: POSITION;
	float3 Normal				: NORMAL;
	float2 Tex0					: TEXCOORD0;
	float3 Tangent				: TEXCOORD1;	//接ベクトル
	float3 BiNormal				: TEXCOORD2;
	float3 WorldPos				: TEXCOORD3; 
	float4 ShadowSpacePos1		: TEXCOORD4;
	float4 ShadowSpacePos2		: TEXCOORD5;
	float4 ShadowSpacePos3		: TEXCOORD6;
	float4 ScreenSpacePos		: TEXCOORD7;

};

struct PS_OUTPUT
{
	float4 color : COLOR0;
	float4 depth : COLOR1;
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
	Normal = mul(In.Normal, g_worldMatrix);
	Tangent = mul(In.Tangent, g_worldMatrix);
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
	Out.Normal = normalize(Normal);
	Out.Tangent = normalize(Tangent);
	Out.BiNormal = normalize(biNormal);
	Out.Tex0 = In.Tex0;
	Out.WorldPos = Pos.xyz;
	Out.ScreenSpacePos = Out.Pos;

	float4 shadowSpacePos[3] = { float4(0.0f, 0.0f, 0.0f, 1.0f), float4(0.0f, 0.0f, 0.0f, 1.0f), float4(0.0f, 0.0f, 0.0f, 1.0f) };
	for (int i = 0;i < 3;i++)
	{
		float4 shadowSpacePosTmp = mul(float4(Pos.xyz, 1.0f), g_lightViewProjMatrix[i]);
		float2 uv = shadowSpacePosTmp.xy / shadowSpacePosTmp.w;
		//
		//if (uv.x >= -1.0f && uv.x <= 1.0f && uv.y >= -1.0f && uv.y <= 1.0f)
		{
			shadowSpacePos[i] = shadowSpacePosTmp;
		}
	}

	Out.ShadowSpacePos1 = shadowSpacePos[0];
	Out.ShadowSpacePos2 = shadowSpacePos[1];
	Out.ShadowSpacePos3 = shadowSpacePos[2];
	return Out;
}

//ピクセルシェーダー
PS_OUTPUT PSMain(VS_OUTPUT In)
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;
	float4 lig = 0.0f;
	if (g_isHasNormalMap)
	{
		float3 normalColor = tex2D(g_normalMapSampler, In.Tex0);
		lig = float4(0.0f, 0.0f, 0.0f, 1.0f);
		//0.0f～1.0fの値を－1.0f～1.0fの正規化されたベクトルに変換
		float3 normalVector = normalColor * 2.0f - 1.0f;
		normalVector = normalize(normalVector);
		float4x4 mat = {
			float4(In.Tangent, 0.0f),
			float4(In.BiNormal, 0.0f),
			float4(In.Normal, 0.0f),
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		normalVector = mul(normalVector, mat);
		//法線マップからとってきたベクトルとライトの方向の内積を取る
		for (int i = 0;i < NUM_DIFFUSE_LIGHT;i++)
		{
			float3 lightDir = g_light.diffuseLightDir[i].xyz;
			lightDir = normalize(lightDir);
			float3 light = max(0, -dot(normal, lightDir)) * g_light.diffuseLightColor[i].xyz;
			lig.xyz += light * max(0, -dot(lightDir, normalVector));
		}
		lig += g_light.ambient;
		lig.w = 1.0f;
	}
	else
	{
		lig = DiffuseLight(normal);
	}
	if (g_isHasSpecularMap)
	{
		//反射ベクトルを求める
		float3 textureNormal = In.Normal;
		textureNormal = normalize(textureNormal);
		float3 gaze = In.WorldPos - g_cameraPos;
		textureNormal *= dot(textureNormal, -gaze);
		gaze += textureNormal * 2.0f;
		gaze = normalize(gaze);

		float3 specColor = tex2D(g_specularMapSampler, In.Tex0).xyz;
		//スペキュラマップを張って絞り(pow)計算をする。
		float3 lightDir = g_light.diffuseLightDir[0].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[0].xyz * length(specColor) * g_light.diffuseLightColor[0].w;
		lightDir = g_light.diffuseLightDir[1].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[1].xyz * length(specColor) * g_light.diffuseLightColor[1].w;
		lightDir = g_light.diffuseLightDir[2].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[2].xyz * length(specColor) * g_light.diffuseLightColor[0].w;
		lightDir = g_light.diffuseLightDir[3].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[3].xyz * length(specColor) * g_light.diffuseLightColor[0].w;
		lig.w = 1.0f;
	}
	if (g_isShadowMapReceiver)
	{
		float4 shadowSpacePos[] =
		{
			In.ShadowSpacePos1,
			In.ShadowSpacePos2,
			In.ShadowSpacePos3
		};
		sampler shadowSampler[] =
		{
			g_shadowMapSampler1,
			g_shadowMapSampler2,
			g_shadowMapSampler3
		};
		for (int i = 0;i < SHADOWMAP_NUM;i++)
		{
			lig *= CalcShadowMap(shadowSampler[i], shadowSpacePos[i]);
		}
	}
	color *= lig;
	PS_OUTPUT Out;
	Out.color = color;
	float depth = In.ScreenSpacePos.z / In.ScreenSpacePos.w;
	Out.depth = float4(depth, 0.0f, 0.0f, 1.0f);
	return Out;
}

//プレイヤー用のピクセルシェーダー
float4 PlayerPSMain(VS_OUTPUT In) : COLOR0
{

	float depth = In.ScreenSpacePos.z / In.ScreenSpacePos.w;
	float2 uv = In.ScreenSpacePos.xy / In.ScreenSpacePos.w;
	uv += 1.0f;
	uv *= 0.5f;
	uv.y = 1.0f - uv.y;

	float4 depthMap = tex2D(g_depthSampler, uv);
	clip(depthMap.x - depth);
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;
	float4 lig = 0.0f;
	if (g_isHasNormalMap)
	{
		float3 normalColor = tex2D(g_normalMapSampler, In.Tex0);
		lig = float4(0.0f, 0.0f, 0.0f, 1.0f);
		//0.0f～1.0fの値を－1.0f～1.0fの正規化されたベクトルに変換
		float3 normalVector = normalColor * 2.0f - 1.0f;
		normalVector = normalize(normalVector);
		float4x4 mat = {
			float4(In.Tangent, 0.0f),
			float4(In.BiNormal, 0.0f),
			float4(In.Normal, 0.0f),
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		normalVector = mul(normalVector, mat);
		//法線マップからとってきたベクトルとライトの方向の内積を取る
		for (int i = 0;i < NUM_DIFFUSE_LIGHT;i++)
		{
			float3 lightDir = g_light.diffuseLightDir[i].xyz;
			lightDir = normalize(lightDir);
			float3 light = max(0, -dot(normal, lightDir)) * g_light.diffuseLightColor[i].xyz;
			lig.xyz += light * max(0, -dot(lightDir, normalVector));
		}
		lig += g_light.ambient;
		lig.w = 1.0f;
	}
	else
	{
		lig  = DiffuseLight(normal);
	}
	if (g_isHasSpecularMap)

	{
		//反射ベクトルを求める
		float3 textureNormal = In.Normal;
		textureNormal = normalize(textureNormal);
		float3 gaze = In.WorldPos - g_cameraPos;
		textureNormal *= dot(textureNormal, -gaze);
		gaze += textureNormal * 2.0f;
		gaze = normalize(gaze);

		float3 specColor = tex2D(g_specularMapSampler, In.Tex0).xyz;
		//スペキュラマップを張って絞り(pow)計算をする。
		for (int i = 0;i < NUM_DIFFUSE_LIGHT;i++)
		{
			float3 lightDir = g_light.diffuseLightDir[i].xyz;
			lightDir = normalize(lightDir);
			lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[i].xyz * length(specColor) * g_light.diffuseLightColor[i].w;
		}
		lig.w = 1.0f;
	}
	if (g_isShadowMapReceiver)
	{

		float4 shadowSpacePos[] =
		{
			In.ShadowSpacePos1,
			In.ShadowSpacePos2,
			In.ShadowSpacePos3,
		};
		sampler shadowSampler[] =
		{
			g_shadowMapSampler1,
			g_shadowMapSampler2,
			g_shadowMapSampler3,
		};
		for (int i = 0;i < SHADOWMAP_NUM;i++)
		{
			CalcShadowMap(shadowSampler[i], shadowSpacePos[i]);
		}
	}
	float3 cameraDir = g_cameraDir;
	cameraDir = normalize(cameraDir);
	float poligonDot = dot(normal, g_cameraDir);
	poligonDot = 1.0f - abs(poligonDot);
	for (int i = 0;i < NUM_DIFFUSE_LIGHT;i++)
	{
		float3 lightDir = g_light.diffuseLightDir[i].xyz;
		lightDir = normalize(lightDir);
		lig += g_light.diffuseLightColor[i] * pow(poligonDot, 3.0f) * 3.0f * max(0.0f, dot(-lightDir, cameraDir));
	}
	color *= lig;
	float4 Out;
	Out = color;
	return Out;
}

/*
シャドウマップ書き込み用の頂点シェーダー
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
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.ShadowSpacePos1 = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	return Out;
}


//シャドウマップ書き込み用のピクセルシェーダー
float4 ShadowMapPSMain(VS_OUTPUT In) : COLOR0
{
	float4 color;
	//深度値を書き込み
	color.x = In.ShadowSpacePos1.z / In.ShadowSpacePos1.w;
	color.yz = 0.0f;
	color.w = 1.0f;
	return color;
}

float4 SilhouettePSMain(VS_OUTPUT In) : COLOR0
{
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

PS_OUTPUT DitheringPSMain(VS_OUTPUT In)
{
	float ditheringMat[4][4] =
	{
		{ 1.0f / 17.0,		9.0f / 17.0f,	3.0f / 17.0f,	11.0f / 17.0f },
		{ 13.0f / 17.0f,	5.0f / 17.0f,	15.0f / 17.0f,	7.0f / 17.0f },
		{ 4.0f / 17.0f,		12.0f / 17.0f,	2.0f / 17.0f,	10.0f / 17.0f },
		{ 16.0f / 17.0f,	8.0f / 17.0f,	14.0f / 17.0f,	6.0f / 17.0f },
	};
	int accuracy = 4000;
	int2 screenPos;
	screenPos.x = (int)((In.ScreenSpacePos.x / In.ScreenSpacePos.w) * accuracy);
	screenPos.y = (int)((In.ScreenSpacePos.y / In.ScreenSpacePos.w) * accuracy);
	//screenPos.x = min(screenPos.x, -screenPos.x);
	//screenPos.y = min(screenPos.y, -screenPos.y);
	screenPos.x = screenPos.x * g_screenWidth / accuracy;
	screenPos.y = screenPos.y * g_screenHeight / accuracy;
	screenPos.x = min(screenPos.x, -screenPos.x);
	screenPos.y = min(screenPos.y, -screenPos.y);
	screenPos.x = (screenPos.x + g_screenWidth) / 2 / 2;
	screenPos.y = (screenPos.y + g_screenHeight) / 2 / 2;
	//screenPos.x = max(screenPos.x, -screenPos.x);
	//screenPos.y = max(screenPos.y, -screenPos.y);
	screenPos.x %= 4;
	screenPos.y %= 4;
	clip(g_ditheringRate - ditheringMat[screenPos.y][screenPos.x]);
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;
	float4 lig = 0.0f;
	if (g_isHasNormalMap)
	{
		float3 normalColor = tex2D(g_normalMapSampler, In.Tex0);
		lig = float4(0.0f, 0.0f, 0.0f, 1.0f);
		//0.0f～1.0fの値を－1.0f～1.0fの正規化されたベクトルに変換
		float3 normalVector = normalColor * 2.0f - 1.0f;
		normalVector = normalize(normalVector);
		float4x4 mat = {
			float4(In.Tangent, 0.0f),
			float4(In.BiNormal, 0.0f),
			float4(In.Normal, 0.0f),
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		normalVector = mul(normalVector, mat);
		//法線マップからとってきたベクトルとライトの方向の内積を取る
		for (int i = 0;i < NUM_DIFFUSE_LIGHT;i++)
		{
			float3 lightDir = g_light.diffuseLightDir[i].xyz;
			lightDir = normalize(lightDir);
			float3 light = max(0, -dot(normal, lightDir)) * g_light.diffuseLightColor[i].xyz;
			lig.xyz += light * max(0, -dot(lightDir, normalVector));
		}
		lig += g_light.ambient;
		lig.w = 1.0f;
	}
	else
	{
		lig = DiffuseLight(normal);
	}
	if (g_isHasSpecularMap)
	{
		//反射ベクトルを求める
		float3 textureNormal = In.Normal;
		textureNormal = normalize(textureNormal);
		float3 gaze = In.WorldPos - g_cameraPos;
		textureNormal *= dot(textureNormal, -gaze);
		gaze += textureNormal * 2.0f;
		gaze = normalize(gaze);
		float3 lightDir = -g_light.diffuseLightDir[0].xyz;
		lightDir = normalize(lightDir);
		float3 specColor = tex2D(g_specularMapSampler, In.Tex0).xyz;
		//スペキュラマップを張って絞り(pow)計算をする。
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[0].xyz * length(specColor) * 3.0f;
		lig.w = 1.0f;
	}

	if (g_isShadowMapReceiver)
	{
		float4 shadowSpacePos[] =
		{
			In.ShadowSpacePos1,
			In.ShadowSpacePos2,
			In.ShadowSpacePos3,
		};
		sampler shadowSampler[] =
		{
			g_shadowMapSampler1,
			g_shadowMapSampler2,
			g_shadowMapSampler3,
		};
		for (int i = 0;i < SHADOWMAP_NUM;i++)
		{
			lig *= CalcShadowMap(shadowSampler[i], shadowSpacePos[i]);
		}
	}
	color *= lig;
	PS_OUTPUT Out;
	Out.color = color;
	float depth = In.ScreenSpacePos.z / In.ScreenSpacePos.w;
	Out.depth = float4(depth, 0.0f, 0.0f, 1.0f);
	return Out;
}

//ピクセルシェーダー
PS_OUTPUT GhostPSMain(VS_OUTPUT In)
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;
	float4 lig = DiffuseLight(normal);
	if (g_isHasNormalMap)
	{
		float3 normalColor = tex2D(g_normalMapSampler, In.Tex0);
		lig = float4(0.0f, 0.0f, 0.0f, 1.0f);
		//0.0f～1.0fの値を－1.0f～1.0fの正規化されたベクトルに変換
		float3 normalVector = normalColor * 2.0f - 1.0f;
		normalVector = normalize(normalVector);

		//法線マップからとってきたベクトルとライトの方向の内積を取る		
		float3 lightDir = g_light.diffuseLightDir[0].xyz;
		lightDir = normalize(lightDir);
		float3 light = max(0, dot(lightDir, normalVector)) * g_light.diffuseLightColor[0].xyz;
		lig.xyz += light;
		lightDir = g_light.diffuseLightDir[1].xyz;
		lightDir = normalize(lightDir);
		light = max(0, dot(lightDir, normalVector)) * g_light.diffuseLightColor[1].xyz;
		lig.xyz += light;
		lightDir = g_light.diffuseLightDir[2].xyz;
		lightDir = normalize(lightDir);
		light = max(0, dot(lightDir, normalVector)) * g_light.diffuseLightColor[2].xyz;
		lig.xyz += light;
		lightDir = g_light.diffuseLightDir[3].xyz;
		lightDir = normalize(lightDir);
		light = max(0, dot(lightDir, normalVector)) * g_light.diffuseLightColor[3].xyz;
		lig.xyz += light;
		lig += g_light.ambient;
		lig.w = 1.0f;
	}
	if (g_isHasSpecularMap)

	{
		//反射ベクトルを求める
		float3 textureNormal = In.Normal;
		textureNormal = normalize(textureNormal);
		float3 gaze = In.WorldPos - g_cameraPos;
		textureNormal *= dot(textureNormal, -gaze);
		gaze += textureNormal * 2.0f;
		gaze = normalize(gaze);

		float3 specColor = tex2D(g_specularMapSampler, In.Tex0).xyz;
		//スペキュラマップを張って絞り(pow)計算をする。
		float3 lightDir = g_light.diffuseLightDir[0].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[0].xyz * length(specColor) * 3.0f;
		lightDir = g_light.diffuseLightDir[1].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[1].xyz * length(specColor) * 3.0f;
		lightDir = g_light.diffuseLightDir[2].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[2].xyz * length(specColor) * 3.0f;
		lightDir = g_light.diffuseLightDir[3].xyz;
		lightDir = normalize(lightDir);
		lig.xyz += pow(max(0, dot(gaze, lightDir)), 10.0f) * g_light.diffuseLightColor[3].xyz * length(specColor) * 3.0f;
		lig.w = 1.0f;
	}

	if (g_isShadowMapReceiver)
	{
		float4 shadowSpacePos[] =
		{
			In.ShadowSpacePos1,
			In.ShadowSpacePos2,
			In.ShadowSpacePos3,
		};
		sampler shadowSampler[] =
		{
			g_shadowMapSampler1,
			g_shadowMapSampler2,
			g_shadowMapSampler3,
		};
		for (int i = 0;i < SHADOWMAP_NUM;i++)
		{
			lig *= CalcShadowMap(shadowSampler[i], shadowSpacePos[i]);
		}
	}
	color *= lig;
	PS_OUTPUT Out;
	float lightColor = length(color.xyz);
	Out.color = float4(lightColor, lightColor, lightColor, 1.0f);
	float depth = In.ScreenSpacePos.z / In.ScreenSpacePos.w;
	Out.depth = float4(depth, 0.0f, 0.0f, 1.0f);
	return Out;
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

//スキンありモデルのシャドウマップ書き込み用テクニック
technique SkinShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 ShadowMapVSMain(true);
		PixelShader = compile ps_3_0 ShadowMapPSMain();
	}
}

//スキンなしモデルのシャドウマップ書き込み用テクニック
technique NoSkinShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 ShadowMapVSMain(false);
		PixelShader = compile ps_3_0 ShadowMapPSMain();
	}
}

//スキンありモデル用のテクニック。
technique SilhouetteSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 SilhouettePSMain();
	}
}

//スキンなしモデル用テクニック。
technique SilhouetteNoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 SilhouettePSMain();
	}
}

//スキンありモデル用のディザリングテクニック
technique DitheringSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 DitheringPSMain();
	}
}

//スキンなしモデル用のディザリングテクニック
technique DitheringNoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 DitheringPSMain();
	}
}

//スキンありモデル用のディザリングテクニック
technique GhostSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 GhostPSMain();
	}
}

//スキンなしモデル用のディザリングテクニック
technique GhostNoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 GhostPSMain();
	}
}

//スキンありモデル用のテクニック。
technique PlayerSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PlayerPSMain();
	}
}

//スキンなしモデル用テクニック。
technique PlayerNoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PlayerPSMain();
	}
}