#pragma once
#include "Contracts.h"

class Controller
{
public:
	Controller(Ui&, Logic&);
	~Controller() = default;
	void Add();
	void Sub();
	//void Mul();
	//void Div();
	//void Mod();
	//void Exp();

private:
	Ui& ui;
	Logic& logic;
	//char operation{};
	//std::vector<std::string> history;
};