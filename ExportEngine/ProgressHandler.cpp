#include "ProgressHandler.h"

IUserInterface* ThrowIfProgressNullPtr(IUserInterface* ui)
{
	if(ui == nullptr)
		throw std::exception("no progress is set");
	return ui;
}

void OpenProgress(IUserInterface* ui, long long range)
{
	ui->OpenProgress("Export", range);
}

void ThrowIfAbort(IUserInterface* ui, int& res)
{
	if(ui->Aborted())
	{
		res = 1;
		throw 5;
	}
}

void AddProgress(IUserInterface* ui, const size_t& totalWritten)
{
	ui->SetProgress(totalWritten);
}

void CloseProgress(IUserInterface* ui)
{
	ui->CloseProgress();
}
