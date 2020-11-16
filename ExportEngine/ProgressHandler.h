#pragma once
#include "ExportData.h"

struct ProgressHandler
{
	ProgressHandler(IUserInterface* UI);
	~ProgressHandler();
	void OpenProgress(const ExportEngineConfig& config);

private:
	IUserInterface* UI;
};