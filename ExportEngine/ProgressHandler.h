#pragma once
#include "ExportData.h"

struct ProgressHandler
{
	ProgressHandler(IUserInterface* UI);
	~ProgressHandler();
	void OpenProgress(const ExportEngineConfig& config);
	void SetProgress(const size_t& totalWritten);

private:
	IUserInterface* UI;
};