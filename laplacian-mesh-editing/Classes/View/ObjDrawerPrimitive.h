#pragma once
#include "MeshDrawerImpl.h"
#include "ObjEntity.h"
#include "Vector3D.h"

class ObjDrawerPrimitive : public MeshDrawerImpl
{
public:
	ObjDrawerPrimitive();

	ObjDrawerPrimitive(EntityImpl* mesh);

	void drawMesh();

	void drawVertexes(std::vector<Vertex*>* vertexContainer);

	void setPointSize(float size);

	void setPointColor(Color3f color);

private:
	float mPointSize;
	float mPointColor[3];
};