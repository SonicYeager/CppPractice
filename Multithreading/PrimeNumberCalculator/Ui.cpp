#include "Ui.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include "windows.h"

void Ui::Run()
{
	Display();
	while(auto range = GetInput())
		onRange(range);
}

size_t Ui::AddProgress() //unused yet
{
	progess.push_back({"Primes are "});
	return progess.size() - 1;
}

void Ui::UpdateProgress(size_t id, PrimeNumber p) //unused yet
{
	progess[id].append(std::to_string(p));
	progess[id].push_back(' ');
	Display();
}

void Ui::Finished(size_t id, Range range) //unused yet
{
	std::ostringstream out;
	out << "for scope [" << range.begin << ", " << range.end << ']';
	progess[id].append(out.str());
	Display();
}

void Ui::ShowResult(Range range, PrimeNumbers primes)
{
	std::cout << "Primes are ";
	for(auto p : primes)
		std::cout << p << ' ';
	std::cout << " for scope [" << range.begin << ", " << range.end << ']' << std::endl;
}

void Ui::Display()
{
	::system("cls");
	std::ostringstream ostr;
	for(auto p : progess)
		ostr << p << '\n';
	ostr << "Enter scope of prime numbers (ESC for abort)\n";
	ostr << input;
	std::cout << ostr.str() << std::endl;
}

auto Ui::GetStartEnd(std::string input)
{
	std::istringstream in(input);
	Range result;
	in >> result.begin;
	in >> result.end;
	return result;
}

Range Ui::GetInput()
{
	while(true)
	{
		// use _getch() to be able to record every input
		char key = _getch();
		if(key == VK_BACK)
			input.pop_back();
		else if(key == VK_ESCAPE)
			break;
		else if(key == '\r')
			return GetStartEnd(std::move(input));
		else
			input.push_back(key);
		Display();
	}
	return {};
}
