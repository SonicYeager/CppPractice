#include "ProcessImage.h"
#include "ParseCmdLine.h"
#include "Configure.h"
#include "Output.h"
#include "LoadSaveImage.h"

void Process(const std::string& sourcePath, const std::string& destinationPath, FilterAlgorithm process)
{
	const RGBImage source = LoadImage::FromBMP(sourcePath);
	RGBImage result(source.Resolution());
	process(source, result);
	SaveImage::ToBMP(destinationPath, result);
}

int ProcessImage::Run(const std::vector<std::string>& args)
{
	ParseCmdLine cmd;
	Configure config;
	Output console;

	cmd.onChooseKernel = [&config](const std::string& filter) {};
	cmd.onDestinationFile = [&config](const std::string& path) { config.SetDestinationFilePath(path); };
	cmd.onSourceFile = [&config](const std::string& path) { config.SetSourceFilePath(path); };
	cmd.onOrientation = [&config](const std::string& orientation) { config.SetOrientation(orientation); };
	cmd.onHelp = [&console] { console.ShowHelp(); };
	cmd.onUnsupportedCmd = [&console](const std::string& cmd, const std::string& arg) {
		console.UnsupportedCmd(cmd, arg);
	};
	cmd.onScaleFactor = [&config](float scale) { config.SetScaleFactor(scale); };
	config.onValid = Process;

	cmd.Process(args);
	return config.Validate();
}
