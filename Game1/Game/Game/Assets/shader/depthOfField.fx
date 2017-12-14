struct VS_INPUT
{
	float4 pos	: POSITION:
	float2 uv	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
};

texture g_sceneTexture;
sampler g_sceneSampler = 
sampler_state 
{
	Texture = <g_sceneTexture>;
	MagFilter = LINEAR;

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
	float4 color = tex2D(g_sceneSampler, In.uv);
	return color;
}

technique 