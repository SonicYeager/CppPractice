#pragma once
#include "ExportData.h"

struct Progress
{
	Progress(IUserInterface* ui);
	~Progress();
	void OpenProgress(long long range);
	void ThrowIfAbort(int& res);
	void AddProgress(const size_t& totalWritten);

private:
	IUserInterface* ui;
	int progress{};
};