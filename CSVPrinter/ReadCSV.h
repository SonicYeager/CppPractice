#pragma once
#include "Interfaces.h"
#include "InternalTypes.h"
#include <fstream>

class ReadCSV : public IResource
{
public:
	CSVRows virtual Read(const std::string&) override;
private:
	CSVRows	parseFile(const CSVRow& filename);
};

