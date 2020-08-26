#include "Person.h"
std::ostream& operator<<(std::ostream & output, Person& input)
{
	output << input.vorname << " " << input.nachname << " " << input.geburtstag.tag << " " << input.geburtstag.monat << " " << input.geburtstag.jahr << " " << input.gehalt << std::endl;
	return output;
}

bool Person::operator==(const Person & otherPers) const
{
	if (
		vorname == otherPers.vorname
		&& nachname == otherPers.nachname
		&& geburtstag.tag == otherPers.geburtstag.tag
		&& geburtstag.monat == otherPers.geburtstag.monat
		&& geburtstag.jahr == otherPers.geburtstag.jahr
		&& gehalt == otherPers.gehalt
		)
		return true;
	else
		return false;
}
