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
	
	MeshViewUI* meshView = new MeshViewUI;
	meshView->show();
	Fl::run();	
	/*int ret;
	new LaplacianOperator(new HalfEdgeEntity(ObjUtility::createObjEntity("worm.obj",ret)));
	MatrixXd m;
	m.resize(10,10);
	
	cout << m;*/
	system("pause");
	return 0;
}
