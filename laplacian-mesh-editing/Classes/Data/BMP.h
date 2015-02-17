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
	//ÿ�����ص��λ��//ֻռ�����ֽڣ�������int����Ȼfread������
	CAI_SYNTHESIZE(short int,m_biBitCount, BiBitCount);
	//λͼȫ������ռ�õ��ֽ���
	CAI_SYNTHESIZE(int,m_biSizeImage, BiSizeImage);
	CAI_SYNTHESIZE(int,m_sizeOfInfoHead, SizeOfInfoHead);
	CAI_SYNTHESIZE(int,m_biWidth, BiWidth);
	CAI_SYNTHESIZE(int,m_biHeight, BiHeight);
	//ֻռ�����ֽڣ�������int����Ȼfread������
	CAI_SYNTHESIZE(short int,m_biPlanes, BiPlanes);
	//ѹ�����ͣ�0Ϊ��ѹ��
	CAI_SYNTHESIZE(int,m_biCompression, BiCompression);
	//ˮƽ�ֱ���(����/��)
	CAI_SYNTHESIZE(int,m_biXPelsPerMeter, BiXPelsPerMeter);
	//��ֱ�ֱ���(����/��)
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