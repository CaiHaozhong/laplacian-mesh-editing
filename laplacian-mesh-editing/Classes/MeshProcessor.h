#pragma once
#include "EntityImpl.h"
#include "OperatorImpl.h"
class MeshProcessor
{
public:
	MeshProcessor(OperatorImpl* meshOperator)
	{
		this->mOperator = meshOperator;
	}
	MeshProcessor();
	~MeshProcessor();

	void mouseClick(int x, int y)
	{
		mOperator->mouseClick(x,y);
	}

	void buttonPush(int funcName)
	{
		mOperator->callFunction(funcName);
	}


private:

	/* ДІРэзг */
	OperatorImpl* mOperator;
};

