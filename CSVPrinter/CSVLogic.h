#pragma once
#include "Interfaces.h"
#include "FormatCSV.h"
#include "InternalTypes.h"

class FormatCSV : public ILogic
{
public:
	CSVRows Format(const CSVRows& csv) override
	{
		return TabulateCSV(csv);
	}
};
