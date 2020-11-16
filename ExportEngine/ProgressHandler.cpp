#include "ProgressHandler.h"

ProgressHandler::ProgressHandler(IUserInterface* UI) 
	: UI(UI)
{
	if(this->UI == nullptr)
		throw std::exception("no progress is set");
}

ProgressHandler::~ProgressHandler()
{
	UI->CloseProgress();
	UI = nullptr;
}

void ProgressHandler::OpenProgress(const ExportEngineConfig& config)
{
	auto range = config.pPI->rangeEnd - config.pPI->rangeStart;
	UI->OpenProgress("Export", range);
}
