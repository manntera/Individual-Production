//���m�N���t�B���^�[

struct VS_INPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos		: POSITION;
	float2 uv 		: TEXCOORD0;
};
texture g_tex;
sampler TextureSampler =
sampler_state
{
	Texture = <g_tex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;

};

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT output;
	output.pos = In.pos;
	output.uv = In.uv;
	return output;
}

float4 PSMain(VS_OUTPUT In) : COLOR0
{
	float4 color = tex2D(TextureSampler, In.uv);
	return length(color.xyz) * 0.5f;
}

technique Monochrome
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}