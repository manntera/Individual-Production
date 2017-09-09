#pragma once
//�A�j���[�V�������Ǘ�����N���X

class Animation
{
public:
	Animation()
	{
		pAnimController = nullptr;
		numAnimSet = 0;
		isBlending = false;
		isInterpolate = false;
		numMaxTracks = 0;
		interpolateEndTime = 0.0f;
		interpolateTime = 0.0f;
	}
	~Animation()
	{

	}
	/*
	������
	anim		�A�j���[�V�����R���g���[���[
	*/
	void Init(ID3DXAnimationController* anim);

	/*
	�A�j���[�V�����̏I���^�C����ݒ肷��B
	animationSetIndex			�A�j���[�V�����C���f�b�N�X�B
	endTime						�A�j���[�V�����̏I���^�C���B-1.0��ݒ肷��ƃA�j���[�V�����t�@�C���ɐݒ肳��Ă���I���^�C���ɂȂ�
	*/
	void SetAnimationEndTime(int animationSetIndex, double endTime)
	{
		animationEndTime[animationSetIndex] = endTime;
	}
	/*
	�A�j���[�V�����̍Đ�
	animationIndex			�Đ��������A�j���[�V�����̃C���f�b�N�X
	*/
	void PlayAnimation(int animationSetIndex);

	/*
	�A�j���[�V�����̍Đ��B�A�j���[�V�����̕�Ԃ��s���܂�
	animationSetIndex				�Đ��������A�j���[�V�����̃C���f�b�N�X
	interpolateTime					��Ԏ��ԁB
	*/
	void PlayAnimation(int animationSetIndex, float interpolateTime);
#if 0
	/*
	�A�j���[�V�����̃u�����f�B���O�Đ�
	animationIndex			�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*/
	void BlendAnimation(int animationSetIndex);
#endif
	/*
	�A�j���[�V�����Z�b�g�̎擾
	*/
	int GetNumAnimationSet() const
	{
		return numAnimSet;
	}
	/*
	�A�j���[�V�����̍X�V
	deltaTime		�X�V���ԁA�P�ʂ͕b
	*/
	void Update(float deltaTime);

private:

	ID3DXAnimationController*				pAnimController;			//�A�j���[�V�����R���g���[���[
	int										numAnimSet;					//�A�j���[�V�����Z�b�g�̐�
	std::unique_ptr<ID3DXAnimationSet*[]>	animationSets;				//�A�j���[�V�����̔z��B
	std::unique_ptr<float[]>				blendRateTable;				//�u�����f�B���O���[�g�̃e�[�u���B
	std::unique_ptr<double[]>				animationEndTime;			//�A�j���[�V�����̏I���^�C���B�f�t�H���g��-1.0�������Ă��āA-1.0�������Ă���ꍇ��ID3DXAnimationSet�̃A�j���[�V�����I���^�C�����D�悳���B
																		//DirectX9�̃A�j���[�V�����Z�b�g��1�b�ȉ��̃A�j���[�V������������@��������Ȃ��B��b�ȉ��̃A�j���[�V�����͂�����K���ݒ�B
	double									localAnimationTime;			//���[�J���A�j���[�V�����^�C��
	int										currentAnimationSetNo;		//���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ�
	int										currentTrackNo;				//���݂̃g���b�N�̔ԍ�
	int										numMaxTracks;				//�A�j���[�V�����g���b�N�̍ő吔
	bool									isBlending;					//�A�j���[�V�����u�����f�B���O���H
	bool									isInterpolate;				//��Ԓ��H
	float									interpolateEndTime;			//��ԏI������
	float									interpolateTime;			//��Ԏ���
};	