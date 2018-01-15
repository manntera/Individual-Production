#include "engineStdafx.h"
#include "SkinModelDataResource.h"
#include "../Graphics/SkinModel/SkinModelData.h"


SkinModelDataResource::SkinModelDataResource()
{

}

SkinModelDataResource::~SkinModelDataResource()
{

}

void SkinModelDataResource::Load(SkinModelData* modelData, Animation* anim, char* fileName)
{
	int hash = MakeHash(fileName);
	auto& map = m_modelDatas.find(hash);
	if (map == m_modelDatas.end())
	{
		SkinModelData* pModelData = new SkinModelData;
		pModelData->LoadModelData(fileName, anim);
		modelData->CloneModelData(*pModelData, anim);
		m_modelDatas.insert({ hash, pModelData });
	}
	else
	{
		modelData->CloneModelData(*map->second, anim);
	}
}