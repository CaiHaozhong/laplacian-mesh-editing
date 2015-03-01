#include "LaplacianOperator.h"
#include <iostream>
#include <fstream>
#define PRINT 1
void printLine(ofstream& outPut)
{
	outPut << "-----------------------------------------------------------------------" << endl;
}
void printMatrix(Eigen::MatrixXd m, char* name)
{
#ifdef PRINT
	ofstream outPut("tmp.txt",ios::app);
	outPut << name << ":" << endl;
	outPut << m << endl;
	printLine(outPut);
	outPut.close();
#endif
}
LaplacianOperator::LaplacianOperator():mState(STATE_CHOOSING_STATIC)
{
}

LaplacianOperator::LaplacianOperator( ObjEntity* mesh ):mState(STATE_CHOOSING_STATIC),OperatorImpl(mesh)
{	
	assert(mesh != nullptr);

	mMeshVertexCount = mesh->getVertexCount();	
	initAdjacentMatrix();
	printMatrix(adjacentMatrix,"adjacentMatrix");
	printMatrix(degreeMatrix,"degreeMatrix");
	//cout << adjacentMatrix << endl;
	//cout << degreeMatrix << endl;
	Eigen::MatrixXd I(mMeshVertexCount,mMeshVertexCount);
	I.setIdentity();
	/* L = I - inv(D)*adj; */
	Eigen::MatrixXd laplacianOperator = I - degreeMatrix.inverse()*adjacentMatrix;
	printMatrix(laplacianOperator,"laplacianOperator");
	Eigen::Matrix<double,Eigen::Dynamic,3> verInput(mMeshVertexCount,3);	
	for (int i = 0; i < mMeshVertexCount; i++)
	{
		Vertex* v = mesh->m_vertexList->at(i);
		verInput(i,0) = v->x; verInput(i,1) = v->y; verInput(i,2) = v->z;
	}

	Eigen::Matrix<double,Eigen::Dynamic,3> deltaInput = laplacianOperator * verInput;
	printMatrix(deltaInput,"deltaInput");
	Eigen::MatrixXd laplacianOperator3D(3*mMeshVertexCount,3*mMeshVertexCount);
	laplacianOperator3D.setZero();
	laplacianOperator3D.topLeftCorner(mMeshVertexCount,mMeshVertexCount) = laplacianOperator;
	laplacianOperator3D.bottomRightCorner(mMeshVertexCount,mMeshVertexCount) = laplacianOperator;
	laplacianOperator3D.block(mMeshVertexCount,mMeshVertexCount,mMeshVertexCount,mMeshVertexCount) = laplacianOperator;


// 	outPut << laplacianOperator << endl << endl;;
 	printMatrix(laplacianOperator3D,"laplacianOperator3D");
// 	outPut.close();
	vector<Vertex*>* meshVertex = mesh->m_vertexList;
	/* operate laplacianOperator3D */
	for (int i = 0; i < mMeshVertexCount; i++)
	{
		/* Generate Matrix A*/
		Vertex* v = meshVertex->at(i);
		vector<Vertex*> vertexInA;
		vertexInA.push_back(v);
		vector<int> adjIndex;
		getAdjVertex(i,adjIndex);
		for (int j = 0; j < adjIndex.size(); j++)
		{
			vertexInA.push_back(meshVertex->at(adjIndex.at(j)));
		}

		Eigen::Matrix<double,Eigen::Dynamic,7> matrixA;
		matrixA.resize(vertexInA.size()*3,7);
		for (int j = 0; j < vertexInA.size(); j++)
		{		
			Eigen::Matrix<double,3,7> m;
			constructMatrix(vertexInA.at(j),m);
			int r = matrixA.rows();			
			matrixA.middleRows<3>(j*3) = m;
			printMatrix(m,"m");			
		}
		
		/* pinv */
		Eigen::Matrix<double,7,Eigen::Dynamic> transposeA = matrixA.transpose();
		Eigen::Matrix<double,7,Eigen::Dynamic> pinvA = (transposeA * matrixA).inverse()*transposeA;
		printMatrix(matrixA,"matrixA");
		printMatrix(transposeA,"transposeA");
		Eigen::Matrix<double,1,Eigen::Dynamic> s = pinvA.row(0);
		Eigen::Matrix<double,1,Eigen::Dynamic> h1 = pinvA.row(1);
		Eigen::Matrix<double,1,Eigen::Dynamic> h2 = pinvA.row(2);
		Eigen::Matrix<double,1,Eigen::Dynamic> h3 = pinvA.row(3);

		Eigen::Matrix<double,1,Eigen::Dynamic> TDeltaX = s*deltaInput(i,0)-h3*deltaInput(i,1)+h2*deltaInput(i,2);
		Eigen::Matrix<double,1,Eigen::Dynamic> TDeltaY = h3*deltaInput(i,0)+s*deltaInput(i,1)-h1*deltaInput(i,2);
		Eigen::Matrix<double,1,Eigen::Dynamic> TDeltaZ = -h2*deltaInput(i,0)-h1*deltaInput(i,1)+s*deltaInput(i,2);

		Eigen::Matrix<double,3,Eigen::Dynamic> TDelta;
		TDelta.resize(3,TDeltaX.cols());
		TDelta.row(0) = TDeltaX; TDelta.row(1) = TDeltaY; TDelta.row(2) = TDeltaZ;

		for (int j = 0; j < 3; j++)
		{
			int opRow = j*mMeshVertexCount+i;
			laplacianOperator3D(opRow,i) -= TDelta(j,0);
			laplacianOperator3D(opRow,i+mMeshVertexCount) -= TDelta(j,1);
			laplacianOperator3D(opRow,i+2*mMeshVertexCount) -= TDelta(j,2);
			int curTDeltaCol = 3;
			for (int a = 0; a < adjIndex.size(); a++)
			{
				int adj = adjIndex.at(a);
				laplacianOperator3D(opRow,adj) -= TDelta(j,curTDeltaCol++);
				laplacianOperator3D(opRow,adj+mMeshVertexCount) -= TDelta(j,curTDeltaCol++);
				laplacianOperator3D(opRow,adj+2*mMeshVertexCount) -= TDelta(j,curTDeltaCol++);
			}
		}		
	}
	int mMeshVertexCount_X3 = 3*mMeshVertexCount;
	A_prime.resize(mMeshVertexCount_X3*2,mMeshVertexCount_X3);
	A_prime.setZero();
	A_prime.topRows(mMeshVertexCount_X3) = laplacianOperator3D;
	int offset = 0;
	for(int j = 0; j < mMeshVertexCount_X3; j+=3)
	{
		A_prime(mMeshVertexCount_X3+j,offset) = 1;
		A_prime(mMeshVertexCount_X3+j+1,offset+mMeshVertexCount) = 1;
		A_prime(mMeshVertexCount_X3+j+2,offset+2*mMeshVertexCount) = 1;
		offset++;
	}
	Eigen::VectorXd b(mMeshVertexCount_X3*2);
	b.setZero();
	for (int j = 0; j < mMeshVertexCount; j++)
	{
		b(mMeshVertexCount_X3+3*j) = meshVertex->at(j)->x;
		b(mMeshVertexCount_X3+3*j+1) = meshVertex->at(j)->y;
		b(mMeshVertexCount_X3+3*j+2) = meshVertex->at(j)->z;
	}					
	b(mMeshVertexCount_X3)  = -21.7391;
	b(mMeshVertexCount_X3+1) = 68.7324;
	b(mMeshVertexCount_X3+2) = 58.9529;	
	Eigen::VectorXd v_p = A_prime.householderQr().solve(b);
	//Eigen::VectorXd v_p = A_prime.jacobiSvd().solve(b);
	

	printMatrix(laplacianOperator3D,"laplacianOperator3D");
	printMatrix(A_prime,"A_prime");
	printMatrix(adjacentMatrix,"adjacentMatrix");
	printMatrix(b,"b");
	printMatrix(v_p,"v_p");	
	
	
	//cout << laplacianOperator;
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
			adjacentMatrix(verIndex,face->v.at(adj)-1) = 1;
		}
	}

	_initDegreeMatrix();
}

void LaplacianOperator::_initDegreeMatrix()
{
	degreeMatrix.resize(mMeshVertexCount,mMeshVertexCount);
	degreeMatrix.setZero();

	for (int i = 0; i < mMeshVertexCount; i++)
	{
		int d = 0;
		for (int j = 0; j < mMeshVertexCount; j++)
		{
			if(adjacentMatrix(i,j) == 1)
			{
				d ++;
			}
		}			
		degreeMatrix(i,i) = d;
	}

}

void LaplacianOperator::constructMatrix( const Vertex* v, Eigen::Matrix<double,3,7>& m )
{
	Eigen::Matrix<double,3,4> leftCols4;
	leftCols4 << v->x,	0,	    v->z,	-v->y,
		v->y,	-v->z,	0,		 v->x,
		v->z,	v->y,	-v->x,	 0;
	m.leftCols<4>() = leftCols4;
	m.rightCols<3>() = Eigen::Matrix<double,3,3>::Identity();
}

void LaplacianOperator::getAdjVertex( int v, vector<int>& adj )
{
	for (int i = 0; i < mMeshVertexCount; i++)
	{
		if(adjacentMatrix(v,i) == 1)
		{
			adj.push_back(i);
		}
	}
}

