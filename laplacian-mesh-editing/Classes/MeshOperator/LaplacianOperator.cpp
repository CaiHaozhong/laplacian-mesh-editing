#include "LaplacianOperator.h"

LaplacianOperator::LaplacianOperator():mState(STATE_CHOOSING_STATIC)
{
}

LaplacianOperator::LaplacianOperator( ObjEntity* mesh ):mState(STATE_CHOOSING_STATIC),OperatorImpl(mesh)
{
	assert(mesh != nullptr);
	
	initAdjacentMatrix();

	mMeshVertexCount = mesh->getVertexCount();
	Eigen::MatrixXd I(mMeshVertexCount,mMeshVertexCount);
	Eigen::MatrixXd laplacianOperator = I - degreeMatrix.inverse()*adjacentMatrix;

}

LaplacianOperator::~LaplacianOperator()
{
}

void LaplacianOperator::mouseClick( int x, int y )
{
	throw std::exception("The method or operation is not implemented.");
}

void LaplacianOperator::callFunction( int funcName )
{
	throw std::exception("The method or operation is not implemented.");
}

void LaplacianOperator::initAdjacentMatrix()
{	
	ObjEntity* objMesh = (ObjEntity*)mMesh;

	
	adjacentMatrix.resize(mMeshVertexCount,mMeshVertexCount);
	adjacentMatrix.setZero();

//	degreeMatrix.resize(vertexArray.size(),vertexArray.size());
//	degreeMatrix.setZero();

	std::vector<Face*>* faceContainer = objMesh->m_faceList;
	for (int i = 0; i < faceContainer->size(); i++)
	{
		Face* face = faceContainer->at(i);
		int faceVertexCount = face->getVertexNum();
		for (int j = 0; j < faceVertexCount; j++)
		{
			int verIndex = face->v.at(j)-1;
			int adj = (j+1)%faceVertexCount;
			adjacentMatrix(verIndex,face->v.at(adj)-1) = 1;
			adj = j - 1;
			if(adj < 0)
				adj += faceVertexCount;				
			adjacentMatrix(verIndex,face->v.at(adj)-1);
		}
	}
}

