#include "pch.h"
#include <iostream>

float Square(float x) {
	return x * x;
}

float FastPower(float a, int n) {
	if (n == 0)
	return 1;
else if (n % 2 == 0)
	return Square(FastPower(a, n / 2));
else
	return a * FastPower(a, n - 1);
}

float FastPowerIterativ(float b, int n) {

	float a = 1;

	while (n != 0)
	{
		if (n % 2 == 0)
		{
			b = b * b;
			n /= 2;
		}
		else
		{
			a *= b;
			n--;
		}
	}
	return a;
}

int main()
{
	for (int k = 2; k < 7; k++)
	{
		for (int i = 0; i < 20; i++)
		{
			std::cout << FastPower(k, i) << " : ";
			std::cout << FastPowerIterativ(k, i) << " | ";

		}
		std::cout << "\n\n";
	}

}
