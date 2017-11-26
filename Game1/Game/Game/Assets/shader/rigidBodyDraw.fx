struct VS_INPUT
{
	float4 pos : POSITION;
	float3 color : COLOR;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float3 color : COLOR; 
};

float4x4 g_viewProjectionMatrix;

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, g_viewProjectionMatrix);
	Out.color = In.color;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : COLOR
{
	return float4(In.color, 1.0f);
}

technique RigidBodyDraw
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}