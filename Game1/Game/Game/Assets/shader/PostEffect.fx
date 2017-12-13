struct VS_INPUT
{
	float4 pos	: POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

texture g_tex;
sampler textureSampler =
sampler_state
{
	Texture = <g_tex>;
	//MipFilter = LINEAR;
	//MinFilter = LINEAR;
	//MagFilter = LINEAR;

	//AddressU = CLAMP;
	//AddressV = CLAMP;
};


VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : COLOR
{
	return tex2D(textureSampler, In.uv);
}


technique PostEffect
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}