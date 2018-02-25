//モノクロフィルター

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
float g_alpha;

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
	float4 srcColor = tex2D(TextureSampler, In.uv);
	float4 destColor = srcColor;
	float alpha = pow(1.0f - g_alpha, 10.0f);
	float len = srcColor.x * 0.299 + srcColor.y * 0.587 + srcColor.z * 0.114;
	srcColor.x = len;
	srcColor.y = len;
	srcColor.z = len;
	float4 color = srcColor * (1.0f - alpha) + destColor * alpha;
	color.w = 1.0f;
	return color;
}

technique Monochrome
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}