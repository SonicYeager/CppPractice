#include "ReadCSV.h"

struct CSVFileReader
{
	void	open(const std::string & filename);
	CSVRow	readRow();
	bool	hasRow();
	~CSVFileReader();
private:
	std::ifstream	input;
};

CSVRows ReadCSV::parseFile(const CSVRow& filename)
{
	CSVRows result;
	CSVFileReader file;
	file.open(filename);
	while (file.hasRow())
	{
		CSVRow row = file.readRow();
		result.push_back(row);
	}
	return result;
}

CSVRows ReadCSV::Read(const std::string& filename)
{
	return parseFile(filename);
}

void CSVFileReader::open(const std::string & filename)
{
	input.open(filename);
}

bool CSVFileReader::hasRow()
{
	bool eof = input.eof();
	return !eof;
}

CSVFileReader::~CSVFileReader()
{
	input.close();
}

CSVRow CSVFileReader::readRow()
{
	CSVRow	result;
	std::getline(input, result);
	return result;
}