#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstring>

void PrintToday() {
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char ptime[30] = {};
	strftime(ptime, 30, "Today is %A", timeinfo);
	std::cout << ptime << std::endl;
}

void PrintDayOfGivenDate(char input[12]) {
	char* splittedinput = strtok(input, ".");
	int day = atoi(splittedinput);
	splittedinput = strtok(nullptr, ".");
	int month = atoi(splittedinput);
	splittedinput = strtok(nullptr, ".");
	int year = atoi(splittedinput);

	time_t newrawtime;
	struct tm* newtime;
	time(&newrawtime);
	newtime = localtime(&newrawtime);
	newtime->tm_mday = day;
	newtime->tm_mon = month - 1;
	newtime->tm_year = year - 1900;
	mktime(newtime);
	char weekday[30] = {};
	strftime(weekday, 30, "%A", newtime);
	printf("%i.%i.%i is a %s",day ,month ,year ,weekday);
}

int main()
{
	PrintToday();

	char input[12] = {};
	std::cout << "Please enter a date with the form (tt.mm.jjjj): " << std::endl;
	std::cin >> input;

	PrintDayOfGivenDate(input);
}
