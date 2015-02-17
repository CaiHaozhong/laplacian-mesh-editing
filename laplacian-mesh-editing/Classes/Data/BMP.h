#ifndef __BMP_H__
#define __BMP_H__

#include<fstream>
#include<assert.h>
#include "def.h"
#define MAX_WIDTH 1024
#define MAX_HEIGHT 1024
using namespace std;
class BMP
{
public:
	BMP();
	~BMP();	
	static BMP* create(char* file);
	void init(char* file);			


	CAI_SYNTHESIZE(int, m_bfOffBits, BfOffBits);
	CAI_SYNTHESIZE(int, m_bfSize, BfSize);
	//每个像素点的位数//只占两个字节，不能用int，不然fread读不了
	CAI_SYNTHESIZE(short int,m_biBitCount, BiBitCount);
	//位图全部像素占用的字节数
	CAI_SYNTHESIZE(int,m_biSizeImage, BiSizeImage);
	CAI_SYNTHESIZE(int,m_sizeOfInfoHead, SizeOfInfoHead);
	CAI_SYNTHESIZE(int,m_biWidth, BiWidth);
	CAI_SYNTHESIZE(int,m_biHeight, BiHeight);
	//只占两个字节，不能用int，不然fread读不了
	CAI_SYNTHESIZE(short int,m_biPlanes, BiPlanes);
	//压缩类型，0为不压缩
	CAI_SYNTHESIZE(int,m_biCompression, BiCompression);
	//水平分辨率(像素/米)
	CAI_SYNTHESIZE(int,m_biXPelsPerMeter, BiXPelsPerMeter);
	//垂直分辨率(像素/米)
	CAI_SYNTHESIZE(int,m_biYPelsPerMeter, BiYPelsPerMeter);
	CAI_SYNTHESIZE(int,m_biClrUsed, BiClrUsed);
	CAI_SYNTHESIZE(int,m_biClrImportant, BiClrImportant);
	
	CAI_SYNTHESIZE(unsigned int,m_colorTableSize, ColorTableSize);		
	CAI_SYNTHESIZE(unsigned char*,colorTable, ColorTable);	
public:		
	//GLubyte data[MAX_WIDTH][MAX_HEIGHT][4];	
	GLubyte* data;
};
#endif // !__BMP_H__