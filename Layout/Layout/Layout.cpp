#include "pch.h"
#include <iostream>

int main()
{
	int x = 8;
	int *px = &x;
	//int **eins = &px;
	int **m[3][3];// = { {&px, &px, &px},{&px, &px, &px},{&px, &px, &px} };

	const char *pchar = "ABC";
	signed char c = -16;
	signed char *p = &c;
}
