#include "ProgressHandler.h"

Progress::Progress(IUserInterface* ui) 
	: ui(ui)
{
	if(this->ui == nullptr)
		throw std::exception("no progress is set");
}

Progress::~Progress()
{
	ui->CloseProgress();
}

void Progress::OpenProgress(long long range)
{
	ui->OpenProgress("Export", range);
}

void Progress::ThrowIfAbort(int& res)
{
	if(ui->Aborted())
	{
		res = 1;
		throw 5;
	}
}

void Progress::AddProgress(const size_t& totalWritten)
{
	ui->SetProgress(totalWritten);
}
