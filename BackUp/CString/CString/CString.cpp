#include "pch.h"
#include <iostream>


int main()
{
	const char *str = "Hello World!\0";
	const char *str2 = "Kello World\0";

	if (*str == *str2)
	{
		std::cout << "It works";
	}

	int laenge = 0;
	while (*str++ != '\0') {
		++laenge;
	}
	str -= laenge + 1;
	std::cout << laenge << ": " << str;
	return 0;
}
