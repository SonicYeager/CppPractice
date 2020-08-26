#pragma once
#include "Puffer.h"
#include "Person.h"
#include <cassert>

template<typename T>
void Print(const T& array)
{
	for (auto elem : array)
	{
		std::cout << elem << ' ';
	}
}

template<typename T>
void Print(const Puffer<T>& buff)
{
	for (size_t i = 0; i < buff.Size(); i++)
	{
		std::cout << buff[i] << ' ';
	}
}

template<>
void Print(const Person& pers)
{
	std::cout << pers.vorname << std::endl;
	std::cout << pers.nachname << std::endl;
	std::cout << pers.geburtstag.tag << std::endl;
	std::cout << pers.geburtstag.monat << std::endl;
	std::cout << pers.geburtstag.jahr << std::endl;
	std::cout << pers.gehalt << std::endl;
}

template<>
void Print(const Puffer<Person>& bufferPerson)
{
	std::cout << "Vorname" << '\t' << "Nachname" << '\t' << "Geburtstag" << '\t' << "Geburtsmonat" << '\t' << "Geburtsjahr" << '\t' << "Gehalt" << std::endl;
	for (size_t i = 0; i < bufferPerson.Size(); i++)
	{
		std::cout << bufferPerson[i];
		/*std::cout << bufferPerson[i].vorname << '\t' 
			<< bufferPerson[i].nachname << '\t' 
			<< bufferPerson[i].geburtstag.tag << '\t' 
			<< bufferPerson[i].geburtstag.monat << '\t' 
			<< bufferPerson[i].geburtstag.jahr << '\t' 
			<< bufferPerson[i].gehalt << std::endl;*/
	}
}

template<typename T, typename U>
bool Find(const T& array, U value)
{
	for (auto elem : array)
		if (value == elem)
			return true;
	return false;
}

template<typename T, typename U>
bool Find(const Puffer<T>& buff, U value)
{
	for (size_t i = 0; i < buff.Size(); i++)
	{
		if (buff[i] == value)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
bool ExampleExpression(const T& value) {
	return value == 10.3;
}

template<typename T, typename U>
bool FindIf(const T& array, U expression)
{
	for (auto elem : array)
		if (expression(elem))
			return true;
	return false;
}

template<typename T, typename U>
bool FindIf(const Puffer<T>& buff, U expression)
{
	for (size_t i = 0; i < buff.Size(); i++)
		if (expression(buff[i]))
			return true;
	return false;
}

template<typename ... T>
void PrintAll(const T& ...content)
{
	(Print(content), ...);
}