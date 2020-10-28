#include "ParseCmdLine.h"


void ParseCmdLine::Process(const Arguments& args)
{
	auto cmdAndArgs = SplitCmdLineArgs(args);
	for(const CmdAndArgs& c : cmdAndArgs)
	{
		CallEvent(c.command, c.argument);
	}
}

auto ParseCmdLine::SplitCmdLineArgs(const Arguments& cmdLineArgs) -> std::vector<CmdAndArgs>
{
	std::vector<CmdAndArgs> result;
	auto arg = std::begin(cmdLineArgs);
	for(; arg != std::end(cmdLineArgs); ++arg)
	{
		// All commands begin with a '-'
		if(arg->front() == '-')
			result.push_back({std::string{arg->begin() + 1, arg->end()}, {}});
		else
			result.back().argument = *arg;
	}

	// No arguments means "show help"
	if(result.empty())
		result.push_back({"help", {}});
	return result;
}

void ParseCmdLine::CallEvent(const std::string& cmd, const std::string& arg)
{
	if(cmd == "help")
		onHelp();
	else if(cmd == "src")
		onSourceFile(arg);
	else if(cmd == "dest")
		onDestinationFile(arg);
	else if(cmd == "kernel")
		onChooseKernel(arg);
	else if(cmd == "scale")
		onScaleFactor(std::stof(arg));
	else if(cmd == "orient")
		onOrientation(arg);
	else if(cmd == "norm")
		onNormalize();
	else
		onUnsupportedCmd(cmd, arg);
}
