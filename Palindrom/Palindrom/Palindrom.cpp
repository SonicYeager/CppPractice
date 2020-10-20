#include "pch.h"
#include <iostream>
#include <cstdio>

bool IsPalindrom(const char* text) {
	const char* temp = text;
	const char* temp2 = text;
	int counter = 0;
	int bcounter = 0;
	while (*text++ != 0){
		counter++;
	}

	if (temp[counter - 1] == '\n')
	{
		for (int i = counter - 2, k = 0; i > -1; i--, k++) {
			if (temp2[k] == temp[i]) {
				bcounter++;
			}
		}
		if (bcounter == counter - 1) {
			return true;
		}
		else
			return false;
	}
	else
	{
		for (int i = counter - 1, k = 0; i > -1; i--, k++) {
			if (temp2[k] == temp[i]) {
				bcounter++;
			}
		}
		if (bcounter == counter) {
			return true;
		}
		else
			return false;
	}

}

void PrintPalindromToFile() {
	std::FILE* pFileIn;
	std::FILE* pFileOut;
	pFileIn = std::fopen("woerter.in", "r");
	pFileOut = std::fopen("woerter.out", "w");

	char word[50];
	while (std::fgets(word, 50, pFileIn) != nullptr)
	{
		bool bIsPalindrom = IsPalindrom(word);
		if (bIsPalindrom) {
			std::fputs(word, pFileOut);
		}
	}
}


int main()
{
	const char* text = "rar";
	bool  bIsPalindrom = IsPalindrom(text);
	if (bIsPalindrom)
	{
		std::cout << "TRUE";
	}
	else
	{
		std::cout << "FALSE";
	}

	PrintPalindromToFile();



}
