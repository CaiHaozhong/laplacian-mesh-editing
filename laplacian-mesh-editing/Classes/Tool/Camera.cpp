#include "Camera.h"

Camera* Camera::instance = NULL;
Camera::Camera()
{
	this->eyex = 0;
	this->eyey = 0;
	this->eyez = 0;

	this->centerx = 0;
	this->centery = 0;
	this->centerz = -1;

	this->upx = 0;
	this->upy = 1;
	this->upz = 0;
}

Camera::~Camera()
{
}

void Camera::look()
{
	gluLookAt(eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz);
}

void Camera::init( GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy, GLdouble upz )
{
	this->eyex = eyex;
	this->eyey = eyey;
	this->eyez = eyez;

	this->centerx = centerx;
	this->centery = centery;
	this->centerz = centerz;

	this->upx = upx;
	this->upy = upy;
	this->upz = upz;
}

Camera* Camera::getInstance()
{
	if (instance == NULL)
	{
		instance = new Camera;
	}
	return instance;
}

GLdouble Camera::getEyeZ()
{
	return eyez;
}

void Camera::setEyeZ( GLdouble ez )
{
	eyez = ez;
}
