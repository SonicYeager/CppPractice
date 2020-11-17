#include "ProgressHandler.h"

IUserInterface* ThrowIfProgressNullPtr(IUserInterface* ui)
{
	if(ui == nullptr)
		throw std::exception("no progress is set");
	return ui;
}
