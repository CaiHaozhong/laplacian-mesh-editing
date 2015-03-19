#pragma once
#include "MeshDrawerImpl.h"
#include "ObjEntity.h"
#include "Vector3D.h"
#include <algorithm>
struct _VertexColor
{
	int index;
	Color3f color;
	bool operator < (const _VertexColor& other) const
	{
		return this->index < other.index;
	}
	_VertexColor(int index, const Color3f& c)
	{
		this->index = index;
		this->color.x = c.x;
		this->color.y = c.y;
		this->color.z = c.z;
	}
	_VertexColor(){}
};
class ObjDrawerPrimitive : public MeshDrawerImpl
{
public:
	ObjDrawerPrimitive();

	ObjDrawerPrimitive(EntityImpl* mesh, Fl_Gl_Window* context);

	void drawMesh();

	void drawVertexes(std::vector<Vertex*>* vertexContainer);

	void setPointSize(float size);

	void setPointColor(Color3f color);

	void setVertexColorWithIndex(int index, const Color3f& c);

	void clearVerticesColor();

private:
	float mPointSize;
	Color3f mPointColor;
	std::vector<_VertexColor> vertexColor;

	void drawVertexWithColor(Vertex* ver, Color3f c);
};