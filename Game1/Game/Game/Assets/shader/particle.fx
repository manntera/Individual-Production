/*
パーティクル用のシェーダー(仮)
*/
struct VS_INPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

float4x4 g_world;

texture g_tex;
sampler TextureSampler =
sampler_state
{
	Texture = <g_tex>;
};

//頂点シェーダー
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, g_world);
	Out.uv = In.uv;
	return Out;

}
//ピクセルシェーダー
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 color = tex2D(TextureSampler, In.uv);
	return color;
}

technique Particle
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain();
		PixelShader	= compile ps_3_0 PSMain();
	}
}