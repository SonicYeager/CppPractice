#include "pch.h"
#include <iostream>

int main()
{
	int x = 123;
	int *p = new int;
	*p = 7;
	int *q = &x;
	int *r = p;
	std::cout << "*p=" << *p << ", *q=" << *q << ", *r=" << *r << '\n';
	int **pp = &p;
	std::cout << "**pp=" << **pp << '\n';
	delete p;
}
