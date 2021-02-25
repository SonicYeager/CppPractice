#pragma once
#include "internaltypes.h"

enum class CARDCOLOR
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	NONE
};

enum class CARDSYMBOL
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	ZERO,
	REVERSE,
	SUSPEND,
	DRAWTWO,
	DRAWFOURCHANGECOLOR,
	CHANGECOLOR
};

struct Card
{
	CARDCOLOR color{};
	CARDSYMBOL symbol{};
};

struct ConsoleRepresentation
{

	std::string Get()
	{

	}

private:
	std::map<CARDCOLOR, std::string> color
	{
		{CARDCOLOR::NONE, "none"},
		{CARDCOLOR::BLUE, "blue"},
		{CARDCOLOR::RED, "red"},
		{CARDCOLOR::YELLOW, "yellow"}
	};
	std::map<CARDSYMBOL, std::string> symbol{};
};

/*
const std::string blueone{"1 - Blue"};
const std::string bluetwo{ "2 - Blue" };
const std::string bluethree{ "3 - Blue" };
const std::string bluefour{ "4 - Blue" };
const std::string bluefive{ "5 - Blue" };
const std::string bluesix{ "6 - Blue" };
const std::string blueseven{ "7 - Blue" };
const std::string blueeight{ "8 - Blue" };
const std::string bluenine{ "9 - Blue" };
const std::string bluezero{ "0 - Blue" };
const std::string bluereverse{ "<< - Blue" };
const std::string bluesuspend{ "/ - Blue" };
const std::string bluedraw{ "+2 - Blue" };

const std::string redone{ "1 - Red" };
const std::string redtwo{ "2 - Red" };
const std::string redthree{ "3 - Red" };
const std::string redfour{ "4 - Red" };
const std::string redfive{ "5 - Red" };
const std::string redsix{ "6 - Red" };
const std::string redseven{ "7 - Red" };
const std::string redeight{ "8 - Red" };
const std::string rednine{ "9 - Red" };
const std::string redzero{ "0 - Red" };
const std::string redreverse{ "<< - Red" };
const std::string redsuspend{ "/ - Red" };
const std::string reddraw{ "+2 - Red" };

const std::string greenone{ "1 - Green" };
const std::string greentwo{ "2 - Green" };
const std::string greenthree{ "3 - Green" };
const std::string greenfour{ "4 - Green" };
const std::string greenfive{ "5 - Green" };
const std::string greensix{ "6 - Green" };
const std::string greenseven{ "7 - Green" };
const std::string greeneight{ "8 - Green" };
const std::string greennine{ "9 - Green" };
const std::string greenzero{ "0 - Green" };
const std::string greenreverse{ "<< - Green" };
const std::string greensuspend{ "/ - Green" };
const std::string greendraw{ "+2 - Green" };

const std::string yellowone{ "1 - Yellow" };
const std::string yellowtwo{ "2 - Yellow" };
const std::string yellowthree{ "3 - Yellow" };
const std::string yellowfour{ "4 - Yellow" };
const std::string yellowfive{ "5 - Yellow" };
const std::string yellowsix{ "6 - Yellow" };
const std::string yellowseven{ "7 - Yellow" };
const std::string yelloweight{ "8 - Yellow" };
const std::string yellownine{ "9 - Yellow" };
const std::string yellowzero{ "0 - Yellow" };
const std::string yellowreverse{ "<< - Yellow" };
const std::string yellowsuspend{ "/ - Yellow" };
const std::string yellowdraw{ "+2 - Yellow" };
*/