#pragma once
#include <FL/Fl_Gl_Window.h>
class EntityImpl;
class MeshDrawerImpl
{
public:
	MeshDrawerImpl():mMesh(nullptr),mContext(nullptr){}

	MeshDrawerImpl(EntityImpl* mesh, Fl_Gl_Window* context)
	{
		mMesh = mesh;
		mContext = context;
	}

	virtual void drawMesh() = 0;

	void postRedraw();
protected:
	EntityImpl* mMesh;
	Fl_Gl_Window* mContext;
};