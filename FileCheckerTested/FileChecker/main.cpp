#include "ProductCode.h"

int main()
{
	FileChecker checker;

	auto result = checker.Check(L"C:\\tmp\\HelloWorld.txt");
	result = checker.Check(L"C:\\tmp\\HelloWorld.txt");
	result = checker.Check(L"C:\\tmp\\HelloWorld.txt");
	result = checker.Check(L"C:\\tmp\\HelloWorld.txt");

	return result == true;
}
