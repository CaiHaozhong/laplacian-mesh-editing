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

	void mousePush(int button, int x, int y)
	{
		mOperator->mousePush(button,x,y);
	}

	void mouseRelease(int button, int x, int y)
	{
		mOperator->mouseRelease(button,x,y);
	}

	void mouseDrag(int button, int x, int y)
	{
		mOperator->mouseDrag(button,x,y);
	}

	void buttonPush(int funcName)
	{
		mOperator->callFunction(funcName);
	}


private:

	/* ДІРэзг */
	OperatorImpl* mOperator;
};

