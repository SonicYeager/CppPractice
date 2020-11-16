#include "Log.h"

void Log::LogFileName(const ExportEngineConfig& config)
{
	std::cout << "Export" << config.targetFileName;
}

void Log::LogRange(const ExportEngineConfig& config)
{
	if(config.pPI->rangeEnd > config.pPI->rangeStart)
		std::cout << " from " << config.pPI->rangeStart << " to " << config.pPI->rangeEnd << " started.\n";
}
