#pragma once
#include "EntityImpl.h"
#include "MeshDrawerImpl.h"
class OperatorImpl
{
public:
	OperatorImpl(EntityImpl* mesh, MeshDrawerImpl* drawer):mMesh(mesh),mDrawer(drawer){};
	OperatorImpl();
	~OperatorImpl();
	
	/* x,y are in OpenGL Coordinate */
	virtual void mousePush(int button, int x, int y) = 0;

	virtual void mouseRelease(int button, int x, int y) = 0;

	virtual void mouseDrag(int button, int x, int y) = 0;

	virtual void callFunction(int funcName) = 0;

	EntityImpl* getMesh() const { return mMesh; }

	void setMesh(EntityImpl* val) { mMesh = val; }

protected:
	EntityImpl* mMesh;
	MeshDrawerImpl* mDrawer;
};