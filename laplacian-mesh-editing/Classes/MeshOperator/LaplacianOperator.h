#pragma once
#include "OperatorImpl.h"
#include "ObjEntity.h"
#include "Eigen/Dense"
#include "Eigen/Sparse"
class LaplacianOperator : public OperatorImpl
{
public:
	static const int FUNC_CONFIRM = 0X01;

	static const int FUNC_CHOOSE_STATIC = 0X02;

	static const int FUNC_MOVE_HANDLE = 0X04;

	LaplacianOperator(ObjEntity* mesh);

	LaplacianOperator();
	~LaplacianOperator();



	virtual void callFunction( int funcName );


private:
	static const int STATE_CHOOSING_STATIC = 0X01;

	static const int STATE_MOVING_HANDLE = 0X02;

	int mState;	

	Eigen::SparseMatrix<double,Eigen::RowMajor> adjacentMatrix;

	/* 每个顶点的度数 */
	Eigen::VectorXd degreeMatrix;

	Eigen::MatrixXd A_prime;

	int mMeshVertexCount;

	void initAdjacentMatrix();

	void computeLaplacianOperator(Eigen::SparseMatrix<double,Eigen::RowMajor>& laplacianOperator);

	void constructMatrix(const Vertex* v, Eigen::Matrix<double,3,7>& m);

	void getAdjVertex(int v, vector<int>& adj);	

	virtual void mousePush( int button, int x, int y );

	virtual void mouseRelease( int button, int x, int y );

	virtual void mouseDrag( int button, int x, int y );

};
