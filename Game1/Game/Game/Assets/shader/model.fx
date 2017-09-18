//�X�L�����f���V�F�[�_�[(4�{�[���X�L�j���O)

#include "LightingFunction.h"

//�X�L���s��
#define MAX_MATRICES 26
float4x3	g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4	g_mViewProj	: VIEWPROJECTION;
float		g_numBone;			//���̐��B

float4x4	g_worldMatrix;			//���[���h�s��
float4x4	g_rotationMatrix;		//��]�s��B
float4x4	g_viewMatrixRotInv;		//�J�����̉�]�s��
float3		g_cameraPos;			//�X�y�L�����p�̃J�������_
float4x4	g_invWorldMatrix;
float4x4	g_lightViewMatrix;
float4x4	g_lightProjMatrix;
float4x4	g_lightViewProjMatrix;
bool	g_flg;

bool	g_isShadowMapCaster;
bool	g_isShadowMapReceiver;

bool	g_isHasNormalMap;			//�@���}�b�v�ێ����Ă���H
bool	g_isHasSpecularMap;			//�@���}�b�v�ێ����Ă���H
texture g_diffuseTexture;			//�f�B�t���[�Y�e�N�X�`��
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

//�@���}�b�v
texture g_normalTexture;		//�@���}�b�v
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

//�X�y�L�����}�b�v
texture g_specularTexture;		//�X�y�L�����}�b�v
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

//�V���h�E�}�b�v
texture g_shadowMapTexture;		//�X�y�L�����}�b�v
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

//���͒��_
struct VS_INPUT
{
	float4 Pos			: POSITION;
	float4 BlendWeights	: BLENDWEIGHT;
	float4 BlendIndices	: BLENDINDICES;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;		//�ڃx�N�g��
	float3 Tex0			: TEXCOORD0;
};

//�o�͒��_�B
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float3 Normal		: NORMAL;
	float2 Tex0			: TEXCOORD0;
	float3 Tangent		: TEXCOORD1;	//�ڃx�N�g��
	float4 LightDir		: TEXCOORD2;
	float3 WorldPos		: TEXCOORD3; 
	float4 LightPos		: TEXCOORD4;
};

/*
���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z����B
In		���͒��_
Pos		���[���h���W�̊i�[��B
Normal	���[���h�@���̊i�[��B
Tangent	���[���h�ڃx�N�g���̊i�[��B
*/
void CalcWorldPosAndNormalFromSkinMatrix(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent)
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	//�u�����h���[�g�B
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
���[���h���W�ƃ��[���h�@�����v�Z�B
In		���͒��_�B
Pos		���[���h���W�̊i�[��B
Normal	���[���h�@���̊i�[��B
Tangent	���[���h�ڃx�N�g���̊i�[��B
*/
void CalcWorldPosAndNormal(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent)
{
	Pos = mul(In.Pos, g_worldMatrix);
	Normal = mul(In.Normal, g_rotationMatrix);
	Tangent = mul(In.Tangent, g_rotationMatrix);
}

/*
���_�V�F�[�_�[
In		���͒��_
hasSkin	�X�L������H
*/
VS_OUTPUT VSMain(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin)
	{
		//�X�L���L��
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent);
	}
	else
	{
		//�X�L������
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

//�s�N�Z���V�F�[�_�[
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
���_�V�F�[�_�[
In		���͒��_
hasSkin	�X�L������H
*/
VS_OUTPUT ShadowMapVSMain(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin)
	{
		//�X�L���L��
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent);
	}
	else
	{
		//�X�L������
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent);
	}
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_lightViewProjMatrix);
	return Out;
}


float4 ShadowMapPSMain(VS_OUTPUT In) : COLOR
{
	return float4(0.7f, 0.7f, 0.7f, 1.0f);
}


//�X�L�����胂�f���p�̃e�N�j�b�N�B
technique SkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//�X�L���Ȃ����f���p�e�N�j�b�N�B
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
