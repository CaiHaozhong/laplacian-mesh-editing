#include "MaterialDataManager.h"
#include <fstream>
#include "ObjUtility.h"
MaterialDataManager::MaterialDataManager(void)
{
	
}


MaterialDataManager::~MaterialDataManager(void)
{
	for(std::map<std::string,MaterialData*>::iterator it = m_map.begin(); it != m_map.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
}

void MaterialDataManager::loadMaterialData( const char* fName ,int& ret)
{
	std::ifstream Input(fName);
	if(!Input.is_open())
	{
		ret = ObjUtility::ReturnType::MTL_FAIL;
		return;
	}
	char key[100];
	char name[100];
	MaterialData* mData = NULL;
	while (Input >> key)
	{
		if(ISEQUAL(key,"#"))
			Input.ignore(1024,'\n');//ºöÂÔÒ»ÐÐ
		else if(ISEQUAL(key,"newmtl"))
		{
 			if(mData != NULL)
 				m_map.insert(std::map<std::string,MaterialData*>::value_type(name,mData));
 			Input >> name;
			mData = new MaterialData;
		}
		else if(ISEQUAL(key,"Ka"))
		{
			Input >> mData->ka[0] >> mData->ka[1] >> mData->ka[2];
		}
		else if(ISEQUAL(key,"Kd"))
		{
			Input >> mData->kd[0] >> mData->kd[1] >> mData->kd[2];
		}
		else if(ISEQUAL(key,"Ks"))
		{
			Input >> mData->ks[0] >> mData->ks[1] >> mData->ks[2];
		}
		else if(ISEQUAL(key,"Ns"))
		{
			Input >> mData->ns;
		}
		else if(ISEQUAL(key,"d"))
		{
			Input >> mData->d;
		}
		else if(ISEQUAL(key,"Tf"))
		{
			Input >> mData->tf[0]>> mData->tf[1]>> mData->tf[2];
		}
		else if(ISEQUAL(key,"illum"))
		{
			Input >> mData->illum;
		}
		else if(ISEQUAL(key, "map_Kd"))
		{
			char file[100];
			Input >> file;
			mData->initTexture(file,ret);
			if (ret == ObjUtility::ReturnType::TEXTURE_FAIL)
			{
				return;
			}
		}
	}
	m_map.insert(std::map<std::string,MaterialData*>::value_type(name,mData));
// 	if(m_index_name.size() > 0 )
// 		m_cur = m_index_name.begin();
}

int MaterialDataManager::getCurrentIndex()
{
	if(m_cur == m_index_name.end())
		return -1;
	return m_cur->first;
}

void MaterialDataManager::next()
{
	if(m_cur != m_index_name.end())
		m_cur++;
}

std::string MaterialDataManager::getMaterialNameByIndex( int index )
{
	return m_index_name.at(index);
}

MaterialData* MaterialDataManager::getMaterialDataByIndex( int index )
{
	//const char* name = getMaterialNameByIndex(index).c_str();
	MaterialData* m = getMaterialDataByName(getMaterialNameByIndex(index).c_str());
	return m;
}

void MaterialDataManager::addIndexName( int index, char* name )
{	
	m_index_name.insert(std::map<int,std::string>::value_type(index,std::string(name)));
	if(m_index_name.size() == 1)
		m_cur = m_index_name.begin();
}

void MaterialDataManager::initCurrentIndex()
{
	m_cur = m_index_name.begin();
}

MaterialData* MaterialDataManager::getMaterialDataByName( const char* name )
{
	return m_map.at(std::string(name));
}
