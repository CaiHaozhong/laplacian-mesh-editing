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
	glGenTextures(1, &tex);                    // ����һ������tex
	//GLenum err = glGetError();
	//printf("%s",gluErrorString(err));
	glBindTexture(GL_TEXTURE_2D, tex);        //������Ȼ��Ը������������������
	//�����������Ϣ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->getBiWidth(),bmp->getBiHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //�����˲�Ϊ�����˲�
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);    //�����˲�
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	delete bmp;
}
