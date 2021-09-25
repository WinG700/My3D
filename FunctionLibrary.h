#pragma once
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;
class FunctionLibrary
{
public:
	static char* LoadBMP(const char* FileName, BITMAPFILEHEADER* FH, BITMAPINFOHEADER* INFO);
	static char* LoadBMP(const char* FileName);
};

