#pragma once

class SkinModelData;
class Animation;

class SkinModelDataResource : Uncopyable
{
public:

	SkinModelDataResource();

	~SkinModelDataResource();

	void Load(SkinModelData* modelData, Animation* anim,  char* fileName);

private:
	std::map<int, SkinModelData*>	m_modelDatas;
};