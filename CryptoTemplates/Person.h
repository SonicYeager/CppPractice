#pragma once
#include <cstdlib>
#include <iostream>
struct Person
{
	bool operator==(const Person& otherPers) const;

	template<typename T>
	T& operator[](size_t index) const 
	{
		switch (index)
		{
		case 0:
			return vorname;
		case 1:
			return nachname;
		case 2:
			return geburtstag.tag;
		case 3:
			return geburtstag.monat;
		case 4:
			return geburtstag.jahr;
		default:
			return ""; // maybe throw a error 
		}
	}

	template<typename T>
	T& operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return vorname;
		case 1:
			return nachname;
		case 2:
			return geburtstag.tag;
		case 3:
			return geburtstag.monat;
		case 4:
			return geburtstag.jahr;
		default:
			return ""; // maybe throw a error 
		}
	}

	const char* vorname;
	const char* nachname;
	struct Geburtstag
	{
		int tag;
		int monat;
		int jahr;
	} geburtstag;
	double gehalt;
};

std::ostream& operator<<(std::ostream &output, Person& input);

