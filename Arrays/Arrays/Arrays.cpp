#include "pch.h"
#include <iostream>

int main()
{
	int matrix[3][3] = {1,0,0,0,1,0,0,0,1};
	int* r = matrix[1];

	for (int i = 0; i < 2; ++i)
	{
		r[i] = i + 1;
	}
	--r;
	r[2] *= -3;
	*(*(matrix + 2) + 1) = 9;

	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < 3; n++)
		{
			std::cout << matrix[i][n];
		}
	}
}
