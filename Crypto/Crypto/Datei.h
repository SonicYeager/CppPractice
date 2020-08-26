#pragma once
#include <iostream>
#include <cstdio>

class Datei
{
public:
	Datei(FILE* file)
		: mp_file(file)
	{}

	Datei(const char* _FileName, const char* _Mode)
	{
		mp_file = fopen(_FileName, _Mode);
	}

	~Datei() 
	{
		fclose(mp_file);
	}

	FILE* GetFile();

private:
	FILE* mp_file = nullptr;
};

