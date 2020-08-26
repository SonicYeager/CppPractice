#include "pch.h"
#include <iostream>

int main()
{
	double matrixA[4][4] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	double matrixB[4][4] = { 16,15,14,13,
							 12,11,10,9,
							 8,7,6,5,
							 4,3,2,1 };
	double matrixC[4][4] = {};

	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			matrixC[i][n] = matrixA[i][n] + matrixB[i][n];
			std::cout << matrixC[i][n] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			int product = 0;

			for (int x = 0; x < 4; x++)
			{
				product += matrixA[x][n] * matrixB[i][x];
			}

			matrixC[i][n] = product;

			std::cout << matrixC[i][n] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";

	int j = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int n = j; n < 4; n++)
		{
			matrixA[i][n] = matrixA[i][n] + matrixA[n][i];
			matrixA[n][i] = matrixA[i][n] - matrixA[n][i];
			matrixA[i][n] = matrixA[i][n] - matrixA[n][i];
		}
		++j;
	}

	j = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int n = j; n < 4; n++)
		{
			matrixB[i][n] = matrixB[i][n] + matrixB[n][i];
			matrixB[n][i] = matrixB[i][n] - matrixB[n][i];
			matrixB[i][n] = matrixB[i][n] - matrixB[n][i];
		}
		++j;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			std::cout << matrixA[i][n] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";

	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			std::cout << matrixB[i][n] << " ";
		}
		std::cout << "\n";
	}

}
