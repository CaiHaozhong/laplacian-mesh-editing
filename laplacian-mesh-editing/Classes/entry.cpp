#include "ObjUtility.h"
#include "LaplacianOperator.h"
#include "HalfEdgeEntity.h"
#include "MeshViewUI.h"
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen; 
#pragma comment(lib,"fltkd.lib")
#pragma comment(lib,"fltkgld.lib")
//#define TEST 1
#define LAP_TEST 2
//#define RUNAPP 3
int main()
{	
#ifdef TEST
	Eigen::SparseMatrix<double,Eigen::RowMajor> A(10,10);
	for (int i = 0; i < 10; i++)
	{
		A.insert(i,1) = (i+1);
		A.insert(i,3) = (i+1)*(i+1);
		A.insert(i,5) = (i+1)*(i+1)*(i+1);
	}
	cout << A << endl << endl;	

	for (Eigen::SparseMatrix<double,Eigen::RowMajor>::InnerIterator it(A,1); it; it++)
	{
		cout << "it.value():" << it.value() << endl;
		cout << it.row() << endl;
		cout << it.col() << endl;
		cout << "--------------------" << endl;
	}

	system("pause");
#endif

#ifdef LAP_TEST
	int ret;
	new LaplacianOperator(ObjUtility::createObjEntity("q3.obj",ret));
#endif

#ifdef RUNAPP
	MeshViewUI* meshView = new MeshViewUI;
	meshView->show();
	Fl::run();
	return 0;
#endif	
}
