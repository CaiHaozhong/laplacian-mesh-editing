#include "LaplacianOperator.h"
#include <iostream>
#include <fstream>
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <Eigen/Eigenvalues>
#include <time.h>
#include "ObjUtility.h"
typedef Eigen::Triplet<double> T;
#define PRINT 1
#undef MY_DEBUG
void printLine(ofstream& outPut)
{
	outPut << "-----------------------------------------------------------------------" << endl;	
}
void printMatrix(Eigen::VectorXd& m, char* name)
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
	clock_t clock_start;
	clock_start = clock();
	mMeshVertexCount = mesh->getVertexCount();	
	initAdjacentMatrix();	
//	printMatrix(adjacentMatrix,"adjacentMatrix");
//	printMatrix(degreeMatrix,"degreeMatrix");

	Eigen::SparseMatrix<double> laplacianOperator;
	computeLaplacianOperator(laplacianOperator);
#ifdef MY_DEBUG
	ofstream out("debug.txt",ios::app);
	out << "laplacianOperator:";
	for (Eigen::SparseMatrix<double>::InnerIterator it(laplacianOperator,283); it; it++)
	{		
		out << it.row() << ' ';
	}
	out << endl;
	
#endif // MY_DEBUG


	//printMatrix(laplacianOperator,"laplacianOperator");
	Eigen::Matrix<double,Eigen::Dynamic,3> verInput(mMeshVertexCount,3);	
	for (int i = 0; i < mMeshVertexCount; i++)
	{
		Vertex* v = mesh->m_vertexList->at(i);
		verInput(i,0) = v->x; verInput(i,1) = v->y; verInput(i,2) = v->z;
	}
	
	Eigen::Matrix<double,Eigen::Dynamic,3> deltaInput = laplacianOperator * verInput;
#ifdef MY_DEBUG
	out << "verInput 283:" << verInput(283,0) << ' ' << verInput(283,1) << ' ' << verInput(283,2) << endl;
	out << "deltaInput 283:" << deltaInput(283,0) << ' ' << deltaInput(283,1) << ' ' << deltaInput(283,2) << endl;	
#endif // MY_DEBUG

	//printMatrix(deltaInput,"deltaInput");
	Eigen::SparseMatrix<double> laplacianOperator3D(6*mMeshVertexCount,3*mMeshVertexCount);	
	laplacianOperator3D.reserve(Eigen::VectorXi::Constant(3*mMeshVertexCount,40));
	//Eigen::MatrixXd laplacianOperator(laplacianOperator);
	vector<Vertex*>* meshVertex = mesh->m_vertexList;
	/* operate laplacianOperator3D */
	for (int i = 0; i < mMeshVertexCount; i++)
	{
		//printf("%d ",i);
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
//			printMatrix(m,"m");
		}		
		Eigen::Matrix<double,7,Eigen::Dynamic> pinvA;

		/* 当该顶点是孤立的的时候，transposeA*matrixA可能是奇异的，因此pinv就会出现-1.#IND*/
		if(adjIndex.size() == 0)
		{
			pinvA.resize(7,3);
			pinvA.setZero();
		}
		else
		{
			Eigen::Matrix<double,7,Eigen::Dynamic> transposeA = matrixA.transpose();
			pinvA = (transposeA * matrixA).inverse()*transposeA;
		}

#ifdef MY_DEBUG
		cout << "MatrixA" << endl << matrixA << endl << endl << "PinvA:" << endl;
		cout << pinvA << endl;
		ofstream sqare("transposeAmatrixA.txt");
		sqare << (transposeA * matrixA) << endl << endl;
		sqare << (transposeA * matrixA).inverse() << endl;
		sqare.close();
#endif // MY_DEBUG

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
			laplacianOperator3D.insert(opRow,i) = j == 0 ? -TDelta(j,0) + laplacianOperator.coeff(i,i) : -TDelta(j,0);
			laplacianOperator3D.insert(opRow,i+mMeshVertexCount) = j == 1 ? -TDelta(j,1) + laplacianOperator.coeff(i,i) : -TDelta(j,1);
			laplacianOperator3D.insert(opRow,i+2*mMeshVertexCount) = j == 2 ? -TDelta(j,2) + laplacianOperator.coeff(i,i) : -TDelta(j,2);
			int curTDeltaCol = 3;
			for (int a = 0; a < adjIndex.size(); a++)
			{
				int adj = adjIndex.at(a);
				laplacianOperator3D.insert(opRow,adj) = j == 0 ? -TDelta(j,curTDeltaCol++) + laplacianOperator.coeff(i,adj) : -TDelta(j,curTDeltaCol++);
				laplacianOperator3D.insert(opRow,adj+mMeshVertexCount) = j == 1 ? -TDelta(j,curTDeltaCol++) + laplacianOperator.coeff(i,adj) :  -TDelta(j,curTDeltaCol++);
				laplacianOperator3D.insert(opRow,adj+2*mMeshVertexCount) = j == 2 ? -TDelta(j,curTDeltaCol++) + laplacianOperator.coeff(i,adj) : -TDelta(j,curTDeltaCol++);
			}
		}		
	}
#ifdef MY_DEBUG
	ofstream outL3d("laplacianOperator3D.txt");
	outL3d << laplacianOperator3D << endl;
	outL3d.close();
#endif


	int mMeshVertexCount_X3 = 3*mMeshVertexCount;
	Eigen::SparseMatrix<double>& A_prime = laplacianOperator3D;	
//	printMatrix(laplacianOperator3D,"laplacianOperator3D");
//	printMatrix(A_prime,"A_prime");

	int offset = 0;
	for(int j = 0; j < mMeshVertexCount_X3; j+=3)
	{
		A_prime.insert(mMeshVertexCount_X3+j,offset) = 1;
		A_prime.insert(mMeshVertexCount_X3+j+1,offset+mMeshVertexCount) = 1;
		A_prime.insert(mMeshVertexCount_X3+j+2,offset+2*mMeshVertexCount) = 1;
		offset++;
	}
 	Eigen::VectorXd b(mMeshVertexCount_X3*2);
 	b.setZero();
	int ret;
	defoMesh = ObjUtility::createObjEntity("defo.obj",ret);
	vector<Vertex*>* defoVertex = defoMesh->m_vertexList;
	int defoSize = defoVertex->size();
	int nodefoSize = mMeshVertexCount;
 	for (int j = 0; j < mMeshVertexCount; j++)
 	{
 		b(mMeshVertexCount_X3+3*j) = defoVertex->at(j)->x;
 		b(mMeshVertexCount_X3+3*j+1) = defoVertex->at(j)->y;
 		b(mMeshVertexCount_X3+3*j+2) = defoVertex->at(j)->z;
 	}					

	A_prime.makeCompressed();


	Eigen::SparseMatrix<double> A_prime_T = Eigen::SparseMatrix<double>(A_prime.transpose());

	Eigen::VectorXd A_prime_T_b = A_prime_T*b;

	Eigen::SparseMatrix<double> sym = A_prime_T*A_prime;

	long t = (clock()-clock_start);
	printf("constructTime:%d\n",t);
#ifdef MY_DEBUG
	ofstream outSym("sym.txt");
	outSym << sym << endl;
	outSym.close();
	ofstream outAprimeT("AprimeT.txt");
	outAprimeT << A_prime_T << endl;
	outAprimeT.close();
	ofstream outAprime("A_prime.txt");
	outAprime << A_prime << endl;
	outAprime.close();
#endif	
#ifdef MY_DEBUG
	Eigen::EigenSolver<Eigen::MatrixXd > es(sym);
	ofstream outEigen("eigenvalues.txt",ios::app);
	outEigen << es.eigenvalues() << endl;
	outEigen.close();
#endif // MY_DEBUG
	
	clock_start = clock();
	//Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > solver;
	Eigen::SimplicialLDLT<Eigen::SparseMatrix<double> > solver;
	solver.compute(sym);
	
	t = (clock()-clock_start);
	printf("factorizationTime:%d\n",t);

	clock_start = clock();
// 	ofstream outLU("LU.txt",ios::app);
// 	outLU << "L:" << endl;
// 	outLU << solver.matrixL() << endl;
// 	outLU << "------------------------------------------------------------------" << endl;
// 	outLU << "U:" << endl;
// 	outLU << solver.matrixU() << endl;
// 	outLU.close();	
	if(solver.info()!= Eigen::Success) {
		// decomposition failed
		return;
	}
	Eigen::VectorXd v_p = solver.solve(A_prime_T_b);

	t = (clock()-clock_start);
	printf("SolveTime:%d\n",t);
	//printMatrix(v_p,"v_p");
	writeToDisk(v_p);

 	if(solver.info()!= Eigen::Success) {
		// solving failed
		return;
	}
//	Eigen::VectorXd v_p = A_prime.householderQr().solve(b);

// 	//Eigen::VectorXd v_p = A_prime.jacobiSvd().solve(b);
// 	
// 
// 	printMatrix(laplacianOperator3D,"laplacianOperator3D");
// 	printMatrix(A_prime,"A_prime");
// 	printMatrix(adjacentMatrix,"adjacentMatrix");
// 	printMatrix(b,"b");
// 	printMatrix(v_p,"v_p");	
// 		
	//cout << laplacianOperator;
}

LaplacianOperator::~LaplacianOperator()
{
}


void LaplacianOperator::callFunction( int funcName )
{
	throw std::exception("The method or operation is not implemented.");
}

void LaplacianOperator::initAdjacentMatrix()
{	
	ObjEntity* objMesh = (ObjEntity*)mMesh;

	
	adjacentMatrix.resize(mMeshVertexCount,mMeshVertexCount);	
	adjacentMatrix.reserve(Eigen::VectorXi::Constant(mMeshVertexCount,10));
	degreeMatrix.resize(mMeshVertexCount);
	degreeMatrix.setZero();
	//std::vector<T> tripletList;


	std::vector<Face*>* faceContainer = objMesh->m_faceList;
	for (int i = 0; i < faceContainer->size(); i++)
	{
		Face* face = faceContainer->at(i);
		int faceVertexCount = face->getVertexNum();
		for (int j = 0; j < faceVertexCount; j++)
		{
			int verIndex = face->v.at(j)-1;
			int adj = (j+1)%faceVertexCount;
			//tripletList.push_back(T(verIndex,face->v.at(adj)-1,1));
			Eigen::SparseMatrix<double>::Scalar val = adjacentMatrix.coeff(verIndex,face->v.at(adj)-1);			
			if(fabs(val-1) > 0.001f)
			{
				adjacentMatrix.insert(verIndex,face->v.at(adj)-1) = 1;
				degreeMatrix(verIndex) += 1;
			}
			adj = j - 1;
			if(adj < 0)
				adj += faceVertexCount;			
			//tripletList.push_back(T(verIndex,face->v.at(adj)-1,1));
			val = adjacentMatrix.coeff(verIndex,face->v.at(adj)-1);
			if(fabs(val-1) > 0.001f)
			{
				adjacentMatrix.insert(verIndex,face->v.at(adj)-1) = 1;
				degreeMatrix(verIndex) += 1;
			}
		}
	}	
	//adjacentMatrix.setFromTriplets(tripletList.begin(),tripletList.end());
	//_initDegreeMatrix();
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
	for (Eigen::SparseMatrix<double>::InnerIterator it(adjacentMatrix,v); it; it++)
	{
		if(it.row() != v)
			adj.push_back(it.row());
	}
	/*for (int i = 0; i < mMeshVertexCount; i++)
	{
		if(adjacentMatrix(v,i) == 1)
		{
			adj.push_back(i);
		}
	}*/
}

void LaplacianOperator::mousePush( int button, int x, int y )
{
	throw std::exception("The method or operation is not implemented.");
}

void LaplacianOperator::mouseRelease( int button, int x, int y )
{
	throw std::exception("The method or operation is not implemented.");
}

void LaplacianOperator::mouseDrag( int button, int x, int y )
{
	throw std::exception("The method or operation is not implemented.");
}

void LaplacianOperator::computeLaplacianOperator( Eigen::SparseMatrix<double>& laplacianOperator )
{
	laplacianOperator.resize(mMeshVertexCount,mMeshVertexCount);
	laplacianOperator.reserve(Eigen::VectorXi::Constant(mMeshVertexCount,10));
	for (int i = 0; i < mMeshVertexCount; i++)
	{
		/* 如果第i个点没有邻接点，即它是一个孤立的点，那么它的laplacian坐标为0 */
		if( adjacentMatrix.innerVector(i).nonZeros() == 0)
		{
			laplacianOperator.insert(i,i) = 0;
			continue;
		}
		laplacianOperator.insert(i,i) = 1;
#ifdef MY_DEBUG
		int adjCount = 0;
#endif		
		for (Eigen::SparseMatrix<double>::InnerIterator it(adjacentMatrix,i); it; it++)
		{
			if(i != it.row())
			{
				laplacianOperator.insert(i,it.row()) = -1/degreeMatrix(i);				
#ifdef MY_DEBUG
			adjCount++;
			if(adjCount >= 10)
				printf("InnerVector size should expand! CurrentMax:%d.\n",adjCount);
#endif
			}
		}
	}
}

void LaplacianOperator::writeToDisk( Eigen::VectorXd& v_p )
{
	ofstream out("SimplicialLDLT_v_p.txt",ios::app);
	int rows = v_p.rows();
	int verCount = rows/3;
	int verCountX2 = verCount*2;
	for (int i = 0; i < verCount; i++)
	{
		out << "v " << v_p(i) << ' ' << v_p(i+verCount) << ' ' << v_p(i+verCountX2) << endl;
	}
	out.close();
}

