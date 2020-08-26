#include "Exceptions.h"

void NoInputException::Print()
{
	std::cout << "No input was given! Check your Input!" << std::endl;
}

void WrongParamException::Print()
{
	std::cout << "Wrong parameter! Check your Input!" << std::endl;
}

void UnknownAlgorithmException::Print()
{
	std::cout << "Unknown algorithm! Check your Input!" << std::endl;
}
