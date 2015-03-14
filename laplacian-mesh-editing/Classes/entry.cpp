#include "ObjUtility.h"
#include "LaplacianOperator.h"
#include "HalfEdgeEntity.h"
#include "MeshViewUI.h"
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen; 
#pragma comment(lib,"fltk.lib")
#pragma comment(lib,"fltkgl.lib")
//#define TEST 1
#define LAP_TEST 2
//#define RUNAPP 3
template<typename T>
class TE{
public:
	T a;
	TE(){
		a.abc();
	}
};
class CI
{
public:
	void abc()
	{
		cout << "CI->abc" << endl;
	}
};
class IA
{
public:
	void abc()
	{
		cout << "IA->abc" << endl;
	}
};
class AG
{
public:
	int arr[5][5];
	AG()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				arr[i][j] = i*j;
			}
		}
	}
	void a()
	{
		cout << "AG->abc" << endl;
	}
	int operator()(int i, int j)
	{
		return arr[i][j];
	}
};
int main()
{	
// 	AG ag;
// 	cout << ag(1,2);
// 	system("pause");
#ifdef TEST
	std::vector<Eigen::Triplet<double> > triplets;
	triplets.push_back(Eigen::Triplet<double>(0,0,5));
	triplets.push_back(Eigen::Triplet<double>(3,5,7));
	triplets.push_back(Eigen::Triplet<double>(8,5,7));
	Eigen::SparseMatrix<double> SA(10,10);
	SA.setFromTriplets(triplets.begin(),triplets.end());
	cout << SA << endl;
	cout << Eigen::SparseMatrix<double>(SA.transpose()) << endl;
	system("pause");
#endif

#ifdef LAP_TEST
	int ret;
	new LaplacianOperator(ObjUtility::createObjEntity("nodefo.obj",ret));
#endif

#ifdef RUNAPP
	MeshViewUI* meshView = new MeshViewUI;
	meshView->show();
	Fl::run();
	return 0;
#endif	
}
