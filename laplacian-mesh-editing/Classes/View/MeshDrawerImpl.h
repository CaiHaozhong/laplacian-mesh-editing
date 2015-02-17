#pragma once
class EntityImpl;
class MeshDrawerImpl
{
public:
	MeshDrawerImpl():mMesh(nullptr){}

	MeshDrawerImpl(EntityImpl* mesh)
	{
		mMesh = mesh;
	}

	virtual void drawMesh() = 0;

protected:
	EntityImpl* mMesh;
};