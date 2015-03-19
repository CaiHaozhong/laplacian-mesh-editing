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
//#define LAP_TEST 2
#define RUNAPP 3
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
#ifdef TEST
	unsigned int svValue[] = {1,2,3,4,5};
	unsigned int mSValue[] = {6,7,8,1,2,3};
	std::vector<unsigned int> sv = std::vector<unsigned int>(svValue,svValue+5);
	std::vector<unsigned int> mSelectedVertices = std::vector<unsigned int>(mSValue,mSValue+6);
	auto svEnd = std::remove_if(sv.begin(),sv.end(),[&](unsigned int svX){
		for(auto it = mSelectedVertices.begin(); it != mSelectedVertices.end(); it++)
		{
			if(svX == *it)
			{
				auto msEnd = std::remove_if(mSelectedVertices.begin(), mSelectedVertices.end(),[=](unsigned int mSx){
					if(mSx == svX)
						return true;
					return false;
				});
				mSelectedVertices.erase(msEnd,mSelectedVertices.end());
				return true;
			}
		}
		return false;
	});
	sv.erase(svEnd,sv.end());
	auto copyBegin = mSelectedVertices.end();
	mSelectedVertices.resize(mSelectedVertices.size()+sv.size());
	std::copy_if(sv.begin(),sv.end(),copyBegin,[&](unsigned int x){
		for(auto it = mSelectedVertices.begin(); it != mSelectedVertices.end(); it++)
		{
			if(x == *it)
				return false;
		}
		return true;
	});
	for_each(sv.begin(), sv.end(), [](unsigned int x){cout << x << ' ';});
	cout << endl;
	for_each(mSelectedVertices.begin(), mSelectedVertices.end(), [](unsigned int x){cout << x << ' ';});
	getchar();
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
