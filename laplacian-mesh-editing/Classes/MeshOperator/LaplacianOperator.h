#pragma once
#include "OperatorImpl.h"
#include "ObjEntity.h"
#include "Eigen/Dense"
class LaplacianOperator : public OperatorImpl
{
public:
	static const int FUNC_CONFIRM = 0X01;

	static const int FUNC_CHOOSE_STATIC = 0X02;

	static const int FUNC_MOVE_HANDLE = 0X04;
	
	LaplacianOperator(ObjEntity* mesh);

	LaplacianOperator();
	~LaplacianOperator();

	virtual void mouseClick( int x, int y );

	virtual void callFunction( int funcName );

	
private:
	static const int STATE_CHOOSING_STATIC = 0X01;

	static const int STATE_MOVING_HANDLE = 0X02;

	int mState;

	Eigen::MatrixXd adjacentMatrix;

	/* ÿ������Ķ��� */
	Eigen::MatrixXd degreeMatrix;

	Eigen::MatrixXd A_prime;

	void initAdjacentMatrix();

	int mMeshVertexCount;
};
