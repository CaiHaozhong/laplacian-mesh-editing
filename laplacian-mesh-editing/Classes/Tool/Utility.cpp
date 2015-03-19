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
Description������ά�ĵ�ͶӰ�ɶ�ά�ĵ� 
Note�����������ڱ任��ʱ�����õ�glPushMatrix��glPopMatrix��
������������glGetDoublev(GL_MODELVIEW_MATRIX,modelview)�õ����ǵ�λ����
�ʽ���ͼ�任������ÿ��glPopMatrixǰ����һ��
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
