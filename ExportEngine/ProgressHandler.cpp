#include "ProgressHandler.h"
#include "LogHandler.h"

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

bool Progress::IsAborded(int& res)
{
	if(ui->Aborted())
	{
		res = 1;
		LogAbortByUser();
		return true;
	}
}

void Progress::AddProgress(size_t written)
{
	progress += written;
	ui->SetProgress(progress);
}
