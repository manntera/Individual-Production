#pragma once
class Texture;
//�e�N�X�`���̃��\�[�X�Ǘ��N���X

class TextureResource : Uncopyable
{
public:
	//�R���X�g���N�^
	TextureResource();

	//�f�X�g���N�^
	~TextureResource();

	//�e�N�X�`�����擾
	Texture* LoadTexture(char* filePath);
private:
	std::map<int, Texture*> m_textures;	//�e�N�X�`��
};