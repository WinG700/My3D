#include "FunctionLibrary.h"


char* FunctionLibrary::LoadBMP(const char* FileName, BITMAPFILEHEADER* FH, BITMAPINFOHEADER* INFO)
{
	// 1. ��ͼƬ�ļ�
	ifstream is(FileName, ifstream::in | ios::binary);
	// 2. ����ͼƬ����
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);
	// 3. �����ڴ滺����
	char* BG_buffer = new char[length];
	// 4. ��ȡͼƬ
	is.read(BG_buffer, length);
	is.close();
	FH = reinterpret_cast<BITMAPFILEHEADER*>(BG_buffer);
	INFO = reinterpret_cast<BITMAPINFOHEADER*>(FH + 1);
	// ���ˣ�ͼƬ�Ѿ��ɹ��ı���ȡ���ڴ棨buffer����
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
