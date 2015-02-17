#pragma once
#include<map>
#include<string>
#include "MaterialData.h"
class MaterialDataManager
{
public:
	MaterialDataManager(void);
	~MaterialDataManager(void);
	MaterialData* getMaterialDataByName(const char* name);
	void loadMaterialData(const char* fName ,int& ret);
	int getCurrentIndex();
	std::string getMaterialNameByIndex(int index);
	MaterialData* getMaterialDataByIndex(int index);
	void next();


	//************************************
	// Method:    addIndexName
	// FullName:  MaterialDataManager::addIndexName
	// Access:    public 
	// Returns:   void	
	// Parameter: int index ��face���±�Ϊindexʱ��Ӧ������Ϊname�Ĳ���
	// Parameter: char * name ���ʵ�����
	//************************************
	void addIndexName(int index, char* name);

	void initCurrentIndex();
private:
	std::map<std::string,MaterialData*> m_map;
	std::map<int,std::string> m_index_name;
	std::map<int,std::string>::iterator m_cur;
};

