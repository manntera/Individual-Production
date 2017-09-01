
//���C�e�B���O�֌W�̊֐��W

#define NUM_DIFFUSE_LIGHT	4			//�f�B�t���[�Y���C�g�̐�

struct SLight
{
	float4 diffuseLightDir[NUM_DIFFUSE_LIGHT];		//�f�B�t���[�Y���C�g�̌���
	float4 diffuseLightColor[NUM_DIFFUSE_LIGHT];	//�f�B�t���[�Y���C�g�̃J���[
	float4 ambient;
};

SLight g_light;


//�f�B�t���[�Y���C�g���v�Z�B
float4 DiffuseLight(float3 normal)
{
	float4 color = 0.0f;
	color += max(0, -dot(normal, g_light.diffuseLightDir[0])) * g_light.diffuseLightColor[0];
	color += max(0, -dot(normal, g_light.diffuseLightDir[1])) * g_light.diffuseLightColor[1];
	color += max(0, -dot(normal, g_light.diffuseLightDir[2])) * g_light.diffuseLightColor[2];
	color += max(0, -dot(normal, g_light.diffuseLightDir[3])) * g_light.diffuseLightColor[3];
	color.xyz += g_light.ambient.xyz;
	color.a = 1.0f;
	return color;
}

float CalcLuminance(float3 color)
{
	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	if (luminance > 1.0f)
	{
		luminance = 1.0f / luminance;
	}
	else
	{
		luminance = 0.0f;
	}
	return luminance;
}