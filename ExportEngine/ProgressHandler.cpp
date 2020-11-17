#include "ProgressHandler.h"

IUserInterface* Progress::SetUi(IUserInterface* ui)
{
	if(ui == nullptr)
		throw std::exception("no progress is set");
	return ui;
}

void Progress::OpenProgress(IUserInterface* ui, long long range)
{
	ui->OpenProgress("Export", range);
}

void Progress::ThrowIfAbort(IUserInterface* ui, int& res)
{
	if(ui->Aborted())
	{
		res = 1;
		throw 5;
	}
}

void Progress::AddProgress(IUserInterface* ui, const size_t& totalWritten)
{
	ui->SetProgress(totalWritten);
}

void Progress::CloseProgress(IUserInterface* ui)
{
	ui->CloseProgress();
}
