#include "pch.h"
#include <iostream>

struct HumanBeing {
	char name[20] = {};
	int age = 0;
	double salary = 0;
};

bool NamesEqual(const HumanBeing& pers1, const HumanBeing& pers2) {
	int equalCounter = 0;
	for (int i = 0; i < 20; i++) {
		if (pers1.name[i] == pers2.name[i])
		{
			equalCounter += 1;
		}
	}
	return  equalCounter == 20 ? true : false;
}

void HumansEqual(const HumanBeing& pers1, const HumanBeing& pers2) {

	bool bequal = NamesEqual(pers1, pers2) and pers1.age == pers2.age and pers1.salary == pers2.salary;
	std::cout << (bequal ? "TRUE" : "FALSE");
}

int main()
{
	HumanBeing person1 = { "Bob", 34, 3000 };

	HumanBeing person2 = { "Bob", 34, 3000 };

	HumansEqual(person1, person2);

}
