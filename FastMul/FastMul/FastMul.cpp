#include "pch.h"
#include <iostream>

int Product(int a, int b) {
	if (b == 0)
		return 0;
	else
		return a + Product(a, b-1);
}

int Add(int a) {
	return a + a;
}

int FastProduct(int a, int b) {
	if (b == 0)
		return 0;
	else if (b % 2 == 0)
		return Add(FastProduct(a, b / 2));
	else
		return a + FastProduct(a, b-1);
}

int FastProductIterative(int a, int b) {

	float sum = 0;

	while (b != 0)
	{
		if (b % 2 == 0)
		{
			a = a + a;
			b /= 2;
		}
		else
		{
			sum += a;
			b--;
		}
	}

	//return a;

	//int sum = a;
	//if (b % 2 == 0) {
	//	sum -= a;
	//}
	//for (b = b/2; b != 0; b--)
	//{
	//	sum += a + a;
	//}

	return sum;
}

int main()
{
	for (int i = 0; i < 21; i++)
	{
		std::cout << Product(7, i) << " : ";
		std::cout << FastProduct(7, i) << " : ";
		std::cout << FastProductIterative(7, i) << " | ";
	}

}
