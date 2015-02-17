//Debug
#pragma once
#include "def.h"

class Camera
{
public:	
	static Camera* instance;
	static Camera* getInstance();
	~Camera();
	void init(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy, GLdouble upz);
	void look();
	GLdouble getEyeZ();
	void setEyeZ(GLdouble ez);
private:
	GLdouble eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz;
	Camera();
};

