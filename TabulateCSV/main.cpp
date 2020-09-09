#include <assert.h>
#include "CSV.h"

int main()
{
	Lines prep = 
	{ 
		{"Name;Strasse;Ort;Alter"},
		{"Peter Pan;Am Hang 5;12345 Einsam;42"},
		{"Maria Schmitz;Gustav-Friedrich-Strasse 45;50123 Bonn;5"}, 
		{"Paul Meier;Aachener Weg 1;87654 Forstheim;65"} 
	};

	Lines expected = 
	{ 
		{"Name         |Strasse                    |Ort            |Alter|"},
		{"-------------+---------------------------+---------------+-----+"},
		{"Peter Pan    |Am Hang 5                  |12345 Einsam   |42   |"},
		{"Maria Schmitz|Gustav-Friedrich-Strasse 45|50123 Bonn     |5    |"}, 
		{"Paul Meier   |Aachener Weg 1             |87654 Forstheim|65   |"} 
	};

	auto res = TabulateCSV(prep);

	assert(expected == res);
}