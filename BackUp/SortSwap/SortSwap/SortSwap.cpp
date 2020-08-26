#include "pch.h"
#include <iostream>


void Swap(int* x, int* y) {
	int t = *x;
	*x = *y;
	*y = t;
}

void SwapSort(int* a, int* b, int* c) {

	while (*a > *b || *a > *c || *b > *c)
	{
		if (*a > *b)
		{
			Swap(a, b);
		}
		if (*a > *c)
		{
			Swap(a , c);
		}
		if (*b > *c)
		{
			Swap(b, c);
		}
	}

}

int main()
{
	int a = 2, b = 0, c = 1;
    std::cout << "Before: " << a << b << c << std::endl; 
	SwapSort(&a, &b, &c);
	std::cout << "After: " << a << b << c << std::endl;
}
