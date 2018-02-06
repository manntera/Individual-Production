#pragma once
//�A�j���[�V�������Ǘ�����N���X

class Animation : Uncopyable
{
public:
	//�R���X�g���N�^
	Animation();

	//�f�X�g���N�^
	~Animation();

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
		m_animationEndTime[animationSetIndex] = endTime;
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
		return m_numAnimSet;
	}
	/*
	�A�j���[�V�����̍X�V
	deltaTime		�X�V���ԁA�P�ʂ͕b
	*/
	void Update(float deltaTime);

	/*
	�A�j���[�V�����̃��[�v�t���O��ݒ�
	animationNum		�ݒ肵�����A�j���[�V�����̔ԍ�
	flg					���[�v�����邩�H
	*/
	void SetAnimationLoopFlg(int animationNum, bool flg)
	{
		m_isAnimationLoop[animationNum] = flg;
	}

	/*
	�A�j���[�V�����̃��[�v�t���O���擾
	animationNum		���[�v�t���O���擾�������A�j���[�V�����̔ԍ�
	*/
	bool GetAnimationLoopFlg(int animationNum) const
	{
		return m_isAnimationLoop[animationNum];
	}

	//���ݍĐ����̃A�j���[�V�����̔ԍ����擾
	int GetCurrentAnimationNum() const
	{
		return m_currentAnimationSetNo;
	}

	//�Đ������H
	bool IsPlay() const
	{
		return m_isPlay;
	}
private:

	ID3DXAnimationController*				m_pAnimController;			//�A�j���[�V�����R���g���[���[
	int										m_numAnimSet;					//�A�j���[�V�����Z�b�g�̐�
	std::unique_ptr<ID3DXAnimationSet*[]>	m_animationSets;				//�A�j���[�V�����̔z��B
	std::unique_ptr<float[]>				m_blendRateTable;				//�u�����f�B���O���[�g�̃e�[�u���B
	std::unique_ptr<double[]>				m_animationEndTime;			//�A�j���[�V�����̏I���^�C���B�f�t�H���g��-1.0�������Ă��āA-1.0�������Ă���ꍇ��ID3DXAnimationSet�̃A�j���[�V�����I���^�C�����D�悳���B
																		//DirectX9�̃A�j���[�V�����Z�b�g��1�b�ȉ��̃A�j���[�V������������@��������Ȃ��B��b�ȉ��̃A�j���[�V�����͂�����K���ݒ�B
	std::unique_ptr<bool[]>					m_isAnimationLoop;
	double									m_localAnimationTime;			//���[�J���A�j���[�V�����^�C��
	int										m_currentAnimationSetNo;		//���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ�
	int										m_currentTrackNo;				//���݂̃g���b�N�̔ԍ�
	int										m_numMaxTracks;				//�A�j���[�V�����g���b�N�̍ő吔
	bool									m_isBlending;					//�A�j���[�V�����u�����f�B���O���H
	bool									m_isInterpolate;				//��Ԓ��H
	float									m_interpolateEndTime;			//��ԏI������
	float									m_interpolateTime;			//��Ԏ���
	bool									m_isPlay;					//�Đ������H
};	