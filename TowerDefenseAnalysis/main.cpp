void RunTests();

#include "Tools.h"
#include "InputTypes.h"

int main()
{
	RunTests();


	//{ INIT

	
	Battlefield battlefield = {"  111111111111111111",
				   "0 1               A1",
				   "1 1 1111111111111111",
				   "1B1 1C        D     ",
				   "1 1 1111111111111111",
				   "1 1               E1",
				   "1 11111111 111111111",
				   "1  F    G1 1H       ",
				   "1111111111 111111111",
				   "                   1",
				   "1111111111 111 111 1",
				   "1I       1 1J1 1K1 1",
				   "11111111 1 1 1 1 1 1",
				   "      L1 1 1 111 111",
				   "   111 1 1 1    M   ",
				   "1111N1 1 1 111111111",
				   "1    1 1 1         1",
				   "1 1111 1 1 111 111 1",
				   "1 1O   1 1 1 1P1 1 1",
				   "1 111111 111 111 111"};
	Turrets turrets = {{'A', 2, 4}, {'B', 2, 3}, {'C', 2, 3}, {'D', 5, 4}, {'E', 1, 4}, {'F', 2, 2}, {'G', 3, 2}, {'H', 5, 2}, {'I', 2, 2}, {'J', 5, 4}, {'K', 1, 5}, {'L', 6, 5}, {'M', 2, 5}, {'N', 3, 3}, {'O', 3, 4}, {'P', 1, 4}};
	IncomingWaves waves = {71, 112, 97, 81, 101, 110, 108, 83, 88, 80, 0, 100, 88, 75, 103, 98, 105, 91, 0, 79, 105, 0, 93, 114, 0, 0, 94, 98, 78, 111, 71, 68, 97};

	//}

	RunTD(battlefield, turrets, waves);

	return 0;
}
