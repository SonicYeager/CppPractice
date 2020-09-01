#include "pch.h"
#include <iostream>

int Pow1(int n) {
	if (n > 0)
	{
		return 2 * Pow1(n - 1);
	}
	return 1;
}

int Pow2(int n) {
	if (n > 0)
	{
		return Pow2(n - 1) + Pow2(n - 1);
	}
	return 1;
}

int main()
{
	for (int i = 0; i < 20; i++)
	{
		std::cout << Pow1(i) << std::endl;
	}
	for (int i = 0; i < 20; i++)
	{
		std::cout << Pow2(i) << std::endl;
	}
}
