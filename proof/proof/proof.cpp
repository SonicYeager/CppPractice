#include "pch.h"
#include <iostream>

int Subtract(int a) {
	static int c = 100;
	c -= a;
	return c;
}

int main()
{
	int a = 2; 
	int b = 2;
	int c = 6;

	b += Subtract(c);

    std::cout << b; 
}
