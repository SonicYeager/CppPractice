#pragma once
#include "ExportData.h"

IUserInterface* ThrowIfProgressNullPtr(IUserInterface* ui);
void OpenProgress(IUserInterface* ui, long long range);
void ThrowIfAbort(IUserInterface* ui, int& res);
void AddProgress(IUserInterface* ui, const size_t& totalWritten);
void CloseProgress(IUserInterface* ui);