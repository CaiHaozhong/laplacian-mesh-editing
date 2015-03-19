#include "Utility.h"
#include <gl/freeglut.h>
#include <cmath>

double Utility::modelViewMatrix[16];

Utility::Utility()
{
}

Utility::~Utility()
{
}

/* 
Description：将三维的点投影成二维的点 
Note：但是由于在变换的时候有用到glPushMatrix和glPopMatrix，
所以在这里用glGetDoublev(GL_MODELVIEW_MATRIX,modelview)得到的是单位矩阵，
故将视图变换矩阵在每次glPopMatrix前保存一下
*/
Vector2D Utility::project( Vector3D p )
{
	Vector3D ret;
	GLint viewport[4];
	//GLdouble modelview[16];
	GLdouble projview[16];
	glGetIntegerv(GL_VIEWPORT,viewport);
	//glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetDoublev(GL_PROJECTION_MATRIX,projview);
 	gluProject(p.x,p.y,p.z,modelViewMatrix,projview,viewport,&(ret.x),&(ret.y),&(ret.z));
// 	long a = ret.x;
// 	long b = (long)(ret.x);
	return Vector2D(ret.x,ret.y);
}

double Utility::pointDistance( Vector2D p1, Vector2D p2 )
{
	long t = (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
	return sqrt((double)t);
}

Vector2D Utility::getScreenSize()
{
	GLint viewport[4];		
	glGetIntegerv(GL_VIEWPORT,viewport);
	return Vector2D(viewport[2],viewport[3]);
}
