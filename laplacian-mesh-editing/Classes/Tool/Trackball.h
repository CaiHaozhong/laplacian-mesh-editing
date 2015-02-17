#pragma once
#include <stdio.h>
#include "Vector3D.h"
#include "Vector3D.cpp"
#include "math.h"
#define EP 0.1
class Trackball
{
public:		
	void getRotateMatrix(int startMouseX, int startMouseY, int endMouseX, int endMouseY, double rotateMatrix[16])
	{
		double z1 = computeZ(startMouseX,startMouseY);
		double z2 = computeZ(endMouseX,endMouseY);
		Vector3D v1(startMouseX,startMouseY,z1);
		Vector3D v2(endMouseX,endMouseY,z2);
		v1.Normalize();
		v2.Normalize();
		Vector3D normalV = v1^v2;
		normalV = -normalV;
		double theta = acos(v1*v2);
		//printf("T:%lf\n",theta);
		double cosHalfTheta = cos(theta/2);
		double sinHalfTheta = sin(theta/2);
		mQuaternion[0] = cosHalfTheta;
		mQuaternion[1] = normalV.x*sinHalfTheta;
		mQuaternion[2] = normalV.y*sinHalfTheta;
		mQuaternion[3] = normalV.z*sinHalfTheta;

		quaternionMul(mLastQuaternion,mQuaternion);

		//snapRotationQuaternion();

		quaternionToMartrix(rotateMatrix);
	}
	Trackball():isVirgin(true)
	{
		mR = 300;
		mLastQuaternion[0] = 1; mLastQuaternion[1] = 0; mLastQuaternion[2] = 0; mLastQuaternion[3] = 0;
	}

	/* 保存上次的旋转 */
	void storeLastRotation()
	{
		mLastQuaternion[0] = mQuaternion[0];
		mLastQuaternion[1] = mQuaternion[1];
		mLastQuaternion[2] = mQuaternion[2];
		mLastQuaternion[3] = mQuaternion[3];
	}

	
private:

	void snapRotationQuaternion()
	{
		Vector3D v(mQuaternion[1],mQuaternion[2],mQuaternion[3]);
		snapRotationAxe(v);
		mQuaternion[1] = v.x;
		mQuaternion[2] = v.y;
		mQuaternion[3] = v.z;
	}

	void snapRotationAxe(Vector3D& v)
	{
		double len = v.Length();
		v.Normalize();
		Vector3D standardX(1,0,0);
		Vector3D standardY(0,1,0);
		Vector3D standardZ(0,0,1);
		if(abs(v*standardX-1) <= EP)		
			v = standardX;		
		else if(abs(v*standardY-1) <= EP)		
			v = standardY;							
		else if(abs(v*standardZ-1) <= EP)		
			v = standardZ;					
		v *= len;
	}

	double computeZ(int x, int y)
	{
		double squareSumXY = x*x+y*y;
		double squareR = mR*mR;
		if(squareSumXY <= squareR/2)
		{
			return sqrt(squareR-squareSumXY);
		}
		else
		{
			return (squareR/2)/sqrt(squareSumXY);
		}
	}

	void quaternionToMartrix(double rotateMatrix[])
	{
		double* ret = new double[16];

		float x2 = mQuaternion[1] * mQuaternion[1];
		float y2 = mQuaternion[2] * mQuaternion[2];
		float z2 = mQuaternion[3] * mQuaternion[3];
		float xy = mQuaternion[1] * mQuaternion[2];
		float xz = mQuaternion[1] * mQuaternion[3];
		float yz = mQuaternion[2] * mQuaternion[3];
		float wx = mQuaternion[0] * mQuaternion[1];
		float wy = mQuaternion[0] * mQuaternion[2];
		float wz = mQuaternion[0] * mQuaternion[3];


		// This calculation would be a lot more complicated for non-unit length quaternions
		// Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
		//   OpenGL
		double temp[16] = { 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f};
		for (int i = 0; i < 16; i++)
		{
			rotateMatrix[i] = temp[i];
		}		
	}

	/* 四元数相乘， 结果赋给q2 */
	void quaternionMul(const double q1[4], double q2[4])
	{
		double a = q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3];
		double b = q1[0] * q2[1] + q1[1] * q2[0] + q1[2] * q2[3] - q1[3] * q2[2];
		double c = q1[0] * q2[2] + q1[2] * q2[0] + q1[3] * q2[1] - q1[1] * q2[3];
		double d = q1[0] * q2[3] + q1[3] * q2[0] + q1[1] * q2[2] - q1[2] * q2[1];				
		q2[0] = a; q2[1] = b; q2[2] = c; q2[3] = d;
	}

	/* 当前旋转的四元数 */
	double mQuaternion[4];

	/* 保存上次旋转的四元数，当前旋转需叠加 */
	double mLastQuaternion[4];

	bool isVirgin;
	double mR;
};

