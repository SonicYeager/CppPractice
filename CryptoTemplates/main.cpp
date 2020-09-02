// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "Person.h"
#include "PufferTools.h"



int main(int argc, const char* argv[])
{
	Person pers{ "Tobias", "Wollrab", 22, 6, 2001, 600 };
	Person persArray[] = {pers, pers, pers};

	Puffer<Person> perBuff = Puffer<Person>(3, persArray);

	double darray[] = {10.3, 9.4, 4.2, 69.69};
	Puffer<double> dBuff = Puffer<double>(4, darray);
	Puffer<char> cBuff = Puffer<char>(6);

	dBuff.Add(20.55);
	dBuff.Add(30.66);
	dBuff.Add(31.66);
	dBuff.Add(32.66);
	dBuff.Add(33.66);
	dBuff.Add(34.66);

	bool barray[] = 
	{
		FindIf(dBuff, ExampleExpression<double>), 
		FindIf(darray, ExampleExpression<double>), 
		Find(darray, 4.2), 
		Find(dBuff, 9.4) 
	};

	Puffer<double> cpy = dBuff;
	Puffer<double> cpyii = Puffer<double>(dBuff);
	cpyii[2] = 404.404;

	if (cpy == cpyii)
	{
		std::cout << "its the same" << std::endl;
	}
	if (perBuff != perBuff)
	{
		std::cout << "its the same" << std::endl;
	}
	cpyii.Data();
	cpyii.Data(300);

	Puffer<double> cpyiii = Puffer<double>(std::move(cpyii));

	std::cout << cpyii.Size() << std::endl;


	PrintAll(perBuff, pers, dBuff, cpy, cpyiii, barray);

}
