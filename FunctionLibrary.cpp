#include "FunctionLibrary.h"


char* FunctionLibrary::LoadBMP(const char* FileName, BITMAPFILEHEADER* FH, BITMAPINFOHEADER* INFO)
{
	// 1. 打开图片文件
	ifstream is(FileName, ifstream::in | ios::binary);
	// 2. 计算图片长度
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);
	// 3. 创建内存缓存区
	char* BG_buffer = new char[length];
	// 4. 读取图片
	is.read(BG_buffer, length);
	is.close();
	FH = reinterpret_cast<BITMAPFILEHEADER*>(BG_buffer);
	INFO = reinterpret_cast<BITMAPINFOHEADER*>(FH + 1);
	// 到此，图片已经成功的被读取到内存（buffer）中
	//cout << FH->bfOffBits << " ";
	//cout << INFO->biWidth << " ";
	//cout << INFO->biHeight << " ";
	return BG_buffer + FH->bfOffBits;
}

char* FunctionLibrary::LoadBMP(const char* FileName)
{
	BITMAPFILEHEADER* FH = nullptr;
	BITMAPINFOHEADER* INFO = nullptr;
	return LoadBMP(FileName, FH, INFO);
}
