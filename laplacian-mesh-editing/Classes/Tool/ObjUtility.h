#pragma once
#include <fstream>
#include<vector>
#include "Vector3D.h"
#include "ObjEntity.h"
#include "MaterialDataManager.h"
using namespace std;
class ObjUtility
{
public:
	ObjUtility();
	~ObjUtility();
	class ReturnType
	{
	public:
		static const int SUCCESS = 0x01;
		static const int OBJ_FAIL = 0x02;
		static const int MTL_FAIL = 0x04;
		static const int TEXTURE_FAIL = 0x08;
	};
	static ObjEntity* createObjEntity(const char* filename, int& ret);

	//************************************
	// Method:    createObjEntity
	// FullName:  ObjUtility::createObjEntity
	// Access:    public static 
	// Returns:   ObjEntity*  (when m_vertexList == NULL or m_faceList == NULL, return NULL)
	// Qualifier:
	// Parameter: vector<Vertex * > * m_vertexList
	// Parameter: vector<TextureCoordinate * > * m_textureCoordinateList
	// Parameter: vector<NormalVector * > * m_normalVectorList
	// Parameter: vector<Face * > * m_faceList
	// Parameter: MaterialDataManager * materialDataManager
	//************************************
	static ObjEntity* createObjEntity(
		vector<Vertex*> *m_vertexList,
		vector<TextureCoordinate*> *m_textureCoordinateList,
		vector<NormalVector*> *m_normalVectorList,
		vector<Face*> *m_faceList,
		MaterialDataManager* materialDataManager
		);		
	
private:
	
	static void splitBySlash(char* str, int len, int& a, int& b, int& c);
};

