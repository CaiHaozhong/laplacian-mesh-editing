#include "ObjUtility.h"
#include "LaplacianOperator.h"
#include "HalfEdgeEntity.h"
#include "MeshViewUI.h"
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen; 
#pragma comment(lib,"fltkd.lib")
#pragma comment(lib,"fltkgld.lib")
int main()
{
	
	
	int ret;

	Eigen::MatrixXd A(3,3);
	Eigen::MatrixXd B(3,9);
	A<< 1, 2, 3,     // Initialize A. The elements can also be
		4, 5, 6,     // matrices, which are stacked along cols
		7, 8, 9;     // and then the rows are stacked.
	B << A, A, A;
	cout << A << endl << endl;
	cout << B;
	new LaplacianOperator(ObjUtility::createObjEntity("q2.obj",ret));
	MeshViewUI* meshView = new MeshViewUI;
	meshView->show();
	Fl::run();
	//system("pause");
	return 0;
}
