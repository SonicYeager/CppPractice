#include "Controller.h"

Controller::Controller(Ui& ui, Logic& logic) 
	: ui(ui)
	, logic(logic)
{
	ui.onAdd = {};
	ui.onSub = {};
	ui.onMul = {};
	ui.onDiv = {};
	ui.onMod = {};
	ui.onExp = {};

	ui.Init();
}

void Controller::Add()
{
}

void Controller::Sub()
{
}

void Controller::Mul()
{
}

void Controller::Div()
{
}

void Controller::Mod()
{
}

void Controller::Exp()
{
}

void Controller::Num()
{
}
