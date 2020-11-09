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
	auto input = ui.GetValues();
	auto res = logic.Add(input.first, input.second);
	ui.Update(res.str());
}

void Controller::Sub()
{
	auto input = ui.GetValues();
	auto res = logic.Sub(input.first, input.second);
	ui.Update(res.str());
}

void Controller::Mul()
{
	auto input = ui.GetValues();
	auto res = logic.Mul(input.first, input.second);
	ui.Update(res.str());
}

void Controller::Div()
{
	auto input = ui.GetValues();
	auto res = logic.Div(input.first, input.second);
	ui.Update(res.str());
}

void Controller::Mod()
{
	auto input = ui.GetValues();
	auto res = logic.Mod(input.first, input.second);
	ui.Update(res.str());
}

void Controller::Exp()
{
	auto input = ui.GetValues();
	auto res = logic.Exp(input.first, input.second);
	ui.Update(res.str());
}
