#include "ProgressHandler.h"

ProgressHandler::ProgressHandler(IUserInterface* UI) 
	: UI(UI)
{}

void ProgressHandler::OpenProgress(IUserInterface* UI, const ExportEngineConfig& config)
{
	auto range = config.pPI->rangeEnd - config.pPI->rangeStart;
	UI->OpenProgress("Export", range);
}
