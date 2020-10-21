#include "FileHandler.h"
#include <fstream>

namespace ConflictSolver 
{
	using Row = std::string;

	struct CSVFileReader
	{
		Row		ReadRow();
		bool	HasRow();
		CSVFileReader(const std::string& filename);
		~CSVFileReader();
	private:
		std::ifstream	input;
	};

	Lines FileHandler::ReadFromFile(const Path& filename)
	{
		Lines result;
		Path path = std::filesystem::absolute(filename);
		CSVFileReader file{ path.string() };
		while (file.HasRow())
		{
			Row row = file.ReadRow();
			result.push_back(row);
		}
		return result;
	}

	Row CSVFileReader::ReadRow()
	{
		Row	result;
		std::getline(input, result);
		return result;
	}


	CSVFileReader::CSVFileReader(const std::string& filename)
	{
		input.open(filename);
	}

	CSVFileReader::~CSVFileReader()
	{
		input.close();
	}

	bool CSVFileReader::HasRow()
	{
		bool eof = input.eof();
		return !eof;
	}

	void WriteRow(const Row&, std::ofstream&);

	void FileHandler::WriteToFile(const Path& filename, const Lines& lines)
	{
		std::ofstream	output;
		output.open(filename);

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			WriteRow(lines[i], output);
			if (i < lines.size() - 1)
			{
				output << std::endl;
			}
		}
	}

	void WriteRow(const Row& row, std::ofstream& output)
	{
		output << row;
	}

}