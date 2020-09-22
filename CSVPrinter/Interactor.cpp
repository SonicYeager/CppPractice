#include "Interactor.h"
#include "InternalTypes.h"
#include <sstream>

std::ostringstream CSVRowsToOutput(const CSVRows&);

void Interactor::DisplayCSV(std::string& filename, std::shared_ptr<IUI> ui, std::shared_ptr<ILogic> logic, std::shared_ptr<IResource> ress)
{
	auto lines = ress->Read(filename);
	auto formatted = logic->Format(lines);
	auto out = CSVRowsToOutput(formatted);
	ui->Print(out);
}

std::ostringstream CSVRowsToOutput(const CSVRows& csv)
{
	std::ostringstream ostr{};
	for (const auto& csvRow : csv)
		ostr << csvRow + "\n";
	return ostr;
}