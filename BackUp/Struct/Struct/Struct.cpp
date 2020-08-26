#include "pch.h"
#include <iostream>

const int b = 100;
const char c[] = "Test";

struct e {
	char e1[4] = {};
	double e2 = 0.0;
};

struct a {
	const int* pb;
	e* pe = nullptr;
	const char* pc;
};

int main()
{
	e e = {"Pi", 3.14159};
	a a = {&b, &e, c};
}
