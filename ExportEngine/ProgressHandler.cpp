#include "ProgressHandler.h"

ProgressHandler::ProgressHandler(IUserInterface* UI) 
	: UI(UI)
{}

inline ProgressHandler::~ProgressHandler()
{
	UI->CloseProgress();
	UI = nullptr;
}

void ProgressHandler::OpenProgress(IUserInterface* UI, const ExportEngineConfig& config)
{
	auto range = config.pPI->rangeEnd - config.pPI->rangeStart;
	UI->OpenProgress("Export", range);
}
