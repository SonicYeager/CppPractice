#include "Customer.h"
#include <iostream>
#include <sstream>

int main()
{
	Customer paul("Paul"), jana("Jana");
	paul.AddRental({{"Planet Erde", Movie::REGULAR}, 3});
	paul.AddRental({{"Planet der Affen", Movie::NEW_RELEASE}, 5});
	paul.AddRental({{"HowTo MAGIX", Movie::NEW_RELEASE}, 1});
	jana.AddRental({{"Der kleine Zwerg", Movie::CHILDRENS}, 2});
	jana.AddRental({{"Murx der Arzt", Movie::CHILDRENS}, 5});

	std::ostringstream out;
	out << paul.Statement() << '\n' << jana.Statement() << '\n';
	const std::string expected = R"(Rental Record for Paul
	Planet Erde	3.5
	Planet der Affen	15
	HowTo MAGIX	3
Amount owed is 21.5
You earned 4 frequent renter points
Rental Record for Jana
	Der kleine Zwerg	1.5
	Murx der Arzt	4.5
Amount owed is 6
You earned 2 frequent renter points
)";
	const std::string actual = out.str();
	if(actual != expected)
	{
		std::cout << "actual:\n" << actual << "\ndiffers from expected:\n" << expected;
	}
	else
	{
		std::cout << "programm runs fine\n";
	}
	system("pause");
	return 0;
}
