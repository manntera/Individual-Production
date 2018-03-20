#pragma once

static const int SHADOWMAP_NUM = 3;

float4  CalcShadowMap(sampler shadowMap, float4 position)
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//���C�g�J�������猩�����W�����ƂɃV���h�E�}�b�v��uv���v�Z
	float2 uv = position.xy / position.w;
	if (uv.x >= -1.0f && uv.x <= 1.0f && uv.y >= -1.0f && uv.y <= 1.0f)
	{
		//�|1.0f�`1.0f�̃X�N���[�����W����0.0f�`1.0f�̃e�N�X�`����uv���W�ɕϊ�
		uv += 1.0f;
		uv *= 0.5f;
		uv.y = 1.0f - uv.y;
		float4 shadow = tex2D(shadowMap, uv);
		//���C�g�J�������猩���[�x�l���v�Z
		float shadowDepth = position.z / position.w;
		shadowDepth = min(1.0f, shadowDepth);
		//�V���h�E�}�b�v�̐[�x�l�Ɣ�r���ăV���h�E�}�b�v�̂�艜�ɂ���Ήe�𗎂Ƃ�
		if (shadow.x < shadowDepth - 0.00005f)
		{
			color = float4(0.7f, 0.7f, 0.7f, 1.0f);
		}
	}
	return color;
}