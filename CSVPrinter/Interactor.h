#pragma once
#include "Interfaces.h"
#include "InternalTypes.h"

class Interactor
{
public:
	void DisplayCSV(std::string&, std::shared_ptr<IUI>, std::shared_ptr<ILogic>, std::shared_ptr<IResource>);
};