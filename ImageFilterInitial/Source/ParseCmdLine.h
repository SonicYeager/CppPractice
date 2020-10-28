#pragma once
#include "Event.h"
#include <vector>
#include <string>

class ParseCmdLine
{
public:
	using Arguments = std::vector<std::string>;
	void Process(const Arguments& args);


	Event<const std::string&> onSourceFile = [](const std::string&) {};
	Event<const std::string&> onDestinationFile = [](const std::string&) {};
	Event<const std::string&> onChooseKernel = [](const std::string&) {};
	Event<float> onScaleFactor = [](float) {};
	Event<const std::string&> onOrientation = [](const std::string&) {};
	Event<> onNormalize = [] {};
	Event<> onHelp = [] {};
	Event<const std::string&, const std::string&> onUnsupportedCmd = [](const std::string&, const std::string&) {};

private:
	struct CmdAndArgs
	{
		std::string command = {};
		std::string argument = {};
	};

	auto SplitCmdLineArgs(const Arguments& cmdLineArgs) -> std::vector<CmdAndArgs>;
	void CallEvent(const std::string& cmd, const std::string& arg);
};
