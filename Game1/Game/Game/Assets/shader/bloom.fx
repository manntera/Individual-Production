
struct VS_INPUT
{
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
};

struct BLUR_OUTPUT
{
	float4 pos	: POSITION;
	float2 uv0	: TEXCOORD0; 
	float2 uv1	: TEXCOORD1; 
	float2 uv2	: TEXCOORD2;
	float2 uv3	: TEXCOORD3;
	float2 uv4	: TEXCOORD4;
	float2 uv5	: TEXCOORD5;
	float2 uv6	: TEXCOORD6;
	float2 uv7	: TEXCOORD7;
};

texture g_sceneTexture;
sampler g_sceneSampler = 
sampler_state
{
	Texture = <g_sceneTexture>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_downTexture0;
sampler g_downSampler0 = 
sampler_state
{
	Texture = <g_downTexture0>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_downTexture1;
sampler g_downSampler1 =
sampler_state
{
	Texture = <g_downTexture1>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_downTexture2;
sampler g_downSampler2 =
sampler_state
{
	Texture = <g_downTexture2>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_downTexture3;
sampler g_downSampler3 =
sampler_state
{
	Texture = <g_downTexture3>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_downTexture4;
sampler g_downSampler4 =
sampler_state
{
	Texture = <g_downTexture4>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

float2 g_sceneTextureSize;
float2 g_offset;
float g_weight[8];

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 color = tex2D(g_sceneSampler, In.uv);
	float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	clip(t - 1.001f);
	color.xyz *= (t - 1.0f);
	color.a = 1.0f;
	return color;
}

float4 CombinePS(VS_OUTPUT In) : COLOR
{
	float4 color;
	color = tex2D(g_downSampler0, In.uv);
	color += tex2D(g_downSampler1, In.uv);
	color += tex2D(g_downSampler2, In.uv);
	color += tex2D(g_downSampler3, In.uv);
	color += tex2D(g_downSampler4, In.uv);
	color *= 0.2f;
	return color;
}

float4 FinalPS(VS_OUTPUT In) : COLOR
{
	float4 color = tex2D(g_sceneSampler, In.uv);
	return clamp(color.x, color.y, color.z);
}

BLUR_OUTPUT XBlurVS(VS_INPUT In)
{
	BLUR_OUTPUT Out;
	Out.pos = In.pos;
	float2 uv = In.uv;
	Out.uv0 = uv + float2(-1.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv1 = uv + float2(-3.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv2 = uv + float2(-5.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv3 = uv + float2(-7.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv4 = uv + float2(-9.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv5 = uv + float2(-11.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv6 = uv + float2(-13.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv7 = uv + float2(-15.0f / g_sceneTextureSize.x, 0.0f);
	return Out;
}

BLUR_OUTPUT YBlurVS(VS_INPUT In)
{
	BLUR_OUTPUT Out;
	Out.pos = In.pos;
	float2 uv = In.uv;
	Out.uv0 = uv + float2(0.0f, -1.0f / g_sceneTextureSize.x);
	Out.uv1 = uv + float2(0.0f, -3.0f / g_sceneTextureSize.x);
	Out.uv2 = uv + float2(0.0f, -5.0f / g_sceneTextureSize.x);
	Out.uv3 = uv + float2(0.0f, -7.0f / g_sceneTextureSize.x);
	Out.uv4 = uv + float2(0.0f, -9.0f / g_sceneTextureSize.x);
	Out.uv5 = uv + float2(0.0f, -11.0f / g_sceneTextureSize.x);
	Out.uv6 = uv + float2(0.0f, -13.0f / g_sceneTextureSize.x);
	Out.uv7 = uv + float2(0.0f, -15.0f / g_sceneTextureSize.x);
	return Out;
}

float4 BlurPS(BLUR_OUTPUT In) : COLOR0
{
	float4 color;
	color = g_weight[0] * (tex2D(g_sceneSampler, In.uv0) + tex2D(g_sceneSampler, In.uv7 + g_offset));
	color += g_weight[1] * (tex2D(g_sceneSampler, In.uv1) + tex2D(g_sceneSampler, In.uv6 + g_offset));
	color += g_weight[2] * (tex2D(g_sceneSampler, In.uv2) + tex2D(g_sceneSampler, In.uv5 + g_offset));
	color += g_weight[3] * (tex2D(g_sceneSampler, In.uv3) + tex2D(g_sceneSampler, In.uv4 + g_offset));
	color += g_weight[4] * (tex2D(g_sceneSampler, In.uv4) + tex2D(g_sceneSampler, In.uv3 + g_offset));
	color += g_weight[5] * (tex2D(g_sceneSampler, In.uv5) + tex2D(g_sceneSampler, In.uv2 + g_offset));
	color += g_weight[6] * (tex2D(g_sceneSampler, In.uv6) + tex2D(g_sceneSampler, In.uv1 + g_offset));
	color += g_weight[7] * (tex2D(g_sceneSampler, In.uv7) + tex2D(g_sceneSampler, In.uv0 + g_offset));
	return color;
}


//輝度抽出用のテクニック
technique LuminanceExtraction
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}


//X方向にブラーをかけるテクニック
technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 XBlurVS();
		PixelShader = compile ps_3_0 BlurPS();
	}
}

//Y方向にブラーをかけるテクニック
technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 YBlurVS();
		PixelShader = compile ps_3_0 BlurPS();
	}
}

//ボカシ合成用テクニック
technique Combine
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 CombinePS();
	}
}

//最終的にメインに合成するテクニック
technique Final
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 FinalPS();
	}
}

