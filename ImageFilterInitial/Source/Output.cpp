#include "Output.h"
#include <iostream>

void Output::ShowHelp()
{
	std::cout << "Use filter app with following commands\n\
-src path \n\
-dest path [default - srcPath + \"Result\"] \n\
-kernel [prewitt, sobel - default=prewitt]\n\
-scale [0.1, 3.0 - default=1.0]\n\
-orient [horizontal, both - default=vertical]\n\
-norm\n";
}

void Output::UnsupportedCmd(const std::string& cmd, const std::string& arg)
{
	std::cout << "command " << cmd << " with argument " << arg << " is unsupported!\n";
}
