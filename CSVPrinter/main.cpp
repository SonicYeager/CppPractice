#include <assert.h>
#include "Interfaces.h"
#include "ConsoleCSVUI.h"
#include "CSVLogic.h"
#include "ReadCSV.h"
#include "Interactor.h"

int main(int argc, char* argv[])
{
	std::string fileArg = argc > 1 ? argv[1] : "SampleCSV.txt";
	Path path = Path(fileArg);
	auto absolutePath = std::filesystem::absolute(path).string();

#if true
#pragma region TESTS
	CSVRows prep =
	{
		{"Name;Strasse;Ort;Alter"},
		{"Peter Pan;Am Hang 5;12345 Einsam;42"},
		{"Maria Schmitz;Gustav-Friedrich-Strasse 45;50123 Bonn;5"},
		{"Paul Meier;Aachener Weg 1;87654 Forstheim;65"}
	};
	CSVRows expected =
	{
		{"Name         |Strasse                    |Ort            |Alter|"},
		{"-------------+---------------------------+---------------+-----+"},
		{"Peter Pan    |Am Hang 5                  |12345 Einsam   |42   |"},
		{"Maria Schmitz|Gustav-Friedrich-Strasse 45|50123 Bonn     |5    |"},
		{"Paul Meier   |Aachener Weg 1             |87654 Forstheim|65   |"}
	};
	auto logic = std::unique_ptr<ILogic>(new FormatCSV());
	auto res = logic->Format(prep);
	assert(expected == res);


	path = Path("SampleCSV.txt");
	absolutePath = std::filesystem::absolute(path).string();
	expected =
	{
		{"Name;Strasse;Ort;Alter"},
		{"Peter Pan;Am Hang 5;12345 Einsam;42"},
		{"Maria Schmitz;Gustav-Friedrich-Strasse 45;50123 Bonn;5"},
		{"Paul Meier;Aachener Weg 1;87654 Forstheim;65"}
	};
	auto ress = std::unique_ptr<IResource>(new ReadCSV());
	res = ress->Read(absolutePath);
	assert(expected == res);
#pragma endregion
#endif

	auto formater = std::shared_ptr<ILogic>(new FormatCSV());
	auto reader = std::shared_ptr<IResource>(new ReadCSV());
	auto ui = std::shared_ptr<IUI>(new CSVUI());
	auto interactor = Interactor();
	interactor.DisplayCSV(absolutePath, ui, formater, reader);
	return 0;
}
