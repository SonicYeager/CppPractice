#pragma once
#include "ExportData.h"

struct ProgressHandler
{
	ProgressHandler(IUserInterface* UI);
	void OpenProgress(IUserInterface* UI, const ExportEngineConfig& config);

private:
	IUserInterface* UI;
};