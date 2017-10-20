#pragma once
//�T�E���h�G���W��

class SoundEngine : Uncopyable
{
public:

	//�R���X�g���N�^
	SoundEngine();

	//�f�X�g���N�^
	~SoundEngine();

	//������
	void Init();

	/*
	�\�[�X�{�C�X���쐬
	format	wave�t�@�C���̃t�H�[�}�b�g
	ret		������\�[�X�{�C�X��Ԃ�
	*/
	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format);

private:
	IXAudio2*				m_xAudio;			//�I�[�f�B�I
	IXAudio2MasteringVoice* m_masteringVoice;	//�}�X�^�[�{�C�X
};
