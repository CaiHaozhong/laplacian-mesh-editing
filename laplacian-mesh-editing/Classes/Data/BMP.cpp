#include "BMP.h"
BMP::BMP():colorTable(NULL),m_colorTableSize(0)
{

}
BMP::~BMP()
{
	delete data;	
}
BMP* BMP::create(char* file)
{
	BMP* bmp = new BMP();
	bmp->init(file);
	return bmp;	
}
void BMP::init(char* file)
{
	assert(file);
	FILE* f;
	fopen_s(&f,file,"rb");

	fseek(f,2,SEEK_SET);
	fread(&m_bfSize,4,1,f);
	fseek(f,4,SEEK_CUR);
	fread(&m_bfOffBits,4,1,f);
	fread(&m_sizeOfInfoHead,4,1,f);
	fread(&m_biWidth,4,1,f);
	fread(&m_biHeight,4,1,f);
	fread(&m_biPlanes,2,1,f);
	fread(&m_biBitCount,2,1,f);
	fread(&m_biCompression,4,1,f);
	fread(&m_biSizeImage,4,1,f);
	fread(&m_biXPelsPerMeter,4,1,f);
	fread(&m_biYPelsPerMeter,4,1,f);
	fread(&m_biClrUsed, 4,1,f);
	fread(&m_biClrImportant,4,1,f);	

	int datasize = m_bfSize-54;
	data = new GLubyte[datasize];
	fseek(f,m_bfOffBits,SEEK_SET);
	fread(data,datasize,1,f);
// 	int len = m_biWidth*3;
// 	while(len % 4 != 0)
// 		len++;
// 	int offset2 = len - m_biWidth*3;
// 	//得到行补位
// 	//int offset = (getBiWidth()*getBiBitCount()+31)/32*4 - ceil(getBiWidth()*(getBiBitCount()/8));
// 	for(int i = 0; i < getBiHeight(); i++)
// 	{
// 		for(int j = 0; j < getBiWidth(); j++)
// 		{
// 			fread(&(data[i][j][2]),1,1,f);
// 			fread(&(data[i][j][1]),1,1,f);
// 			fread(&(data[i][j][0]),1,1,f);
// 			data[i][j][3] = 255;				
// 		}
// 		fseek(f,offset2,SEEK_CUR);//略过剩下的补位字节
// 	}
			
	fclose(f);

}

