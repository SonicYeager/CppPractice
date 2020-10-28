#pragma once
#include <string>

class Output
{
public:
	void ShowHelp();
	void UnsupportedCmd(const std::string& cmd, const std::string& arg);
};
