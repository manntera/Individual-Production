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
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_blurTexture;
sampler g_blurSampler =
sampler_state
{
	Texture = <g_blurTexture>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_depthTexture;
sampler g_depthSampler =
sampler_state
{
	Texture = <g_depthTexture>;
	MagFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
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
	float2 uv = In.uv + g_offset;
	float4 color = tex2D(g_sceneSampler, uv);
	float4 blurColor = tex2D(g_blurSampler, uv);
	float depth = tex2D(g_depthSampler, uv).x;
	if (depth <= 0.1f)
	{
		depth *= 10.0f;
	}
	else if(depth <= 0.9f)
	{
		depth = 1.0f;
	}
	else
	{
		depth = 10.0f * (1.0f - depth);
	}
	blurColor.w = (1.0f - depth);

	return blurColor;
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

float4 BlurPS(BLUR_OUTPUT In) : COLOR
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


technique Combine
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}

technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 XBlurVS();
		PixelShader = compile ps_3_0 BlurPS();
	}
}

technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 YBlurVS();
		PixelShader = compile ps_3_0 BlurPS();
	}
}