#pragma once
#include "def.h"

class MaterialData
{
public:
	MaterialData(void);
	~MaterialData(void);
	//************************************
	// Method:    hasMapPic( «∑Ò”–Ã˘ÕºÕº∆¨£©
	// FullName:  MaterialData::hasMapPic
	// Access:    public 
	// Returns:   bool	
	//************************************
	bool hasTexture();
	void initTexture(const char* file,int& ret);
	GLuint getTexture();

public:
	GLdouble ka[3], kd[3], ks[3];
	GLdouble tf[3];
	GLdouble ns;
	GLdouble d;
	unsigned int illum;	
	GLuint tex;
};

