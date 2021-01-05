#pragma once
#include "ExportData.h"

struct Progress
{
	Progress(IUserInterface* ui);
	~Progress();
	void OpenProgress(long long range);
	bool IsAborded(int& res);
	void AddProgress(size_t written);

private:
	IUserInterface* ui;
	int progress{};
};