#pragma once
#include "Interfaces.h"
#include <iostream>

class CSVUI : public IUI
{
public:
	void Print(const std::ostringstream& ostr) override
	{
		std::cout << ostr.str() << std::endl;
	}
};