#include "pch.h"
#include <iostream>

int a[4] = { 4,3,2,1 };
int i = 0;

void Swap(int* x, int* y) {
	int t;
	t = *x;
	*x = *y;
	*y = t;
}

int F() {
	i++;
	return i;
}

int main()
{
	Swap(&i, &a[F()]);
	std::cout << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << ", " << std::endl;
}
