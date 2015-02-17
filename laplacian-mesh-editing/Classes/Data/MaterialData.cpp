#include "MaterialData.h"
#include "BMP.h"
#include "ObjUtility.h"


MaterialData::MaterialData(void)
{
	
	tex = 0;
}


MaterialData::~MaterialData(void)
{
}

bool MaterialData::hasTexture()
{
	return tex != 0;
}

GLuint MaterialData::getTexture()
{
	return tex;
}

void MaterialData::initTexture( const char* file ,int& ret)
{
	char pa[100];
	sprintf_s(pa,"%s",file);
	ifstream testOpen(file);
	if(!testOpen.is_open())
	{
		ret = ObjUtility::ReturnType::TEXTURE_FAIL;
		return;
	}
	BMP* bmp = BMP::create(pa);
	glGenTextures(1, &tex);                    // 创建一个纹理，tex
	//GLenum err = glGetError();
	//printf("%s",gluErrorString(err));
	glBindTexture(GL_TEXTURE_2D, tex);        //绑定纹理，然后对该纹理区添加纹理数据
	//设置纹理的信息
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->getBiWidth(),bmp->getBiHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);    //线性滤波
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	delete bmp;
}
