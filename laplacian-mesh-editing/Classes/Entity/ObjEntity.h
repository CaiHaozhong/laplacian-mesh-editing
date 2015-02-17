#pragma once
#include "EntityImpl.h"
#include "MaterialDataManager.h"
#include "Vector3D.h"
#include "Face.h"

class ObjEntity : public EntityImpl
{
public:
	//Data
	vector<Vertex*> *m_vertexList;
	vector<TextureCoordinate*> *m_textureCoordinateList;
	vector<NormalVector*> *m_normalVectorList;
	vector<Face*> *m_faceList;	
	MaterialDataManager* materialDataManager;

	//Data retriver
	vector<Face*> *getFaces();
	Vertex* vertexAt(int i);
	TextureCoordinate* textureCoordinateAt(int i);
	NormalVector* normalVectorAt(int i);

	int getVertexCount();

	ObjEntity();
	~ObjEntity();
	
	void OnDraw();
	void useMaterial(MaterialData* mData);
private:

};
