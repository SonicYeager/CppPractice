#include "ExportEngine.h"
#include <iostream>

int main()
{
	ExportEngine exporter;
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID | RENAME_FILENAME_IF_EXIST; // | RGB_EXPORT;
	config.pUserInterface = IUserInterface::Create();
	exporter.Bounce(config);
	delete config.pUserInterface;
	std::cin.get();
	return 0;
}
