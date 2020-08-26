#include "pch.h"
#include <iostream>

int main()
{
	double r, A, U, PI = 4 * atan(1);
	std::cout << "Bitte Radius eingeben! <mit kommastellen moeglich>"; 
	std::cin >> r;

	A = PI*(r*r);
	U = 2 * PI*r;

	std::cout << "Der Flaecheninhalt des Kreises betreagt: " << A << "\nDer Umfang des Kreises betraegt: " << U;

	bool exit = 0;
	while (!exit)
	{
		bool countryValue;
		double input, output;
		const double translationFac = 0.12;

		std::cout << "Geben sie den umzurechnenden Betrag ein: ";
		std::cin >> input;
		std::cout << "Geben sie \"1\" fuer Europaeische Waehrung ein, und \"0\" fuer US-Amerikanische!: ";
		std::cin >> countryValue;

		if (countryValue == true)
		{
			output = input + (input * translationFac);
		}
		else
		{
			output = input - (input * translationFac);
		}

		std::cout << output;
		std::cout << "\nZum Beenden des Programms \"1\" eingeben, zum fortfahren \"0\": ";
		std::cin >> exit;
	}

	//unsigned short ux = 65535;
	//unsigned short uy = ux + 1;
	//char a = 65;
	//char b = a + 1;
	//short x = 767;
	//short y = x + 1;

	//std::cout << uy << b << y;

	//signed char sum = 127;
	//sum = ~sum ^ -1;

	//std::cout << (int)sum;
}

