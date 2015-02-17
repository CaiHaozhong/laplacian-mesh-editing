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
	// Parameter: int index 当face的下标为index时，应用名字为name的材质
	// Parameter: char * name 材质的名字
	//************************************
	void addIndexName(int index, char* name);

	void initCurrentIndex();
private:
	std::map<std::string,MaterialData*> m_map;
	std::map<int,std::string> m_index_name;
	std::map<int,std::string>::iterator m_cur;
};

