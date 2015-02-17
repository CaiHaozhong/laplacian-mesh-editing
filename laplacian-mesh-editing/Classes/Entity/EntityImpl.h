#pragma once
#include "Vector3D.h"
typedef Vector3D Size3D;
class EntityImpl
{
public:	
	EntityImpl(){}
	EntityImpl(EntityImpl* other)
	{
		this->setCenter(other->getCenter());
		this->setSize(other->getSize());
	}

	virtual void OnDraw() = 0;

	Size3D getSize(){ return mSize; }

	void setSize(const Size3D& size){ mSize = size; }

	Vector3D getCenter() { return mCenter; }

	void setCenter(const Vector3D& cen){ mCenter = cen; }
protected:
	Size3D mSize;
	Vector3D mCenter;
};

