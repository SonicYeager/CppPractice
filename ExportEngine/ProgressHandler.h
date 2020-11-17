#pragma once
#include "ExportData.h"

struct Progress
{
	IUserInterface* SetUi(IUserInterface* ui);
	void OpenProgress(IUserInterface* ui, long long range);
	void ThrowIfAbort(IUserInterface* ui, int& res);
	void AddProgress(IUserInterface* ui, const size_t& totalWritten);
	void CloseProgress(IUserInterface* ui);

private:
	IUserInterface* ui = nullptr;
	int progress{};
};