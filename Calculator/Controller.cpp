#include "Controller.h"

//Controller::Controller(Ui& ui, Logic& logic) 
//	: ui(ui)
//	, logic(logic)
//{
//	ui.onAdd = std::bind(&Controller::Add, this);
//	ui.onSub = std::bind(&Controller::Sub, this);
//	ui.onMul = std::bind(&Controller::Mul, this);
//	ui.onDiv = std::bind(&Controller::Div, this);
//	ui.onMod = std::bind(&Controller::Mod, this);
//	ui.onExp = std::bind(&Controller::Exp, this);
//
//	ui.Init();
//}
//
//std::string ComposeHistory(double left, double right, char op, const std::stringstream& result)
//{
//	std::stringstream res;
//	res << left << " " << op << " " << right << " = " << result.str();
//	return res.str();
//}
//
//void Controller::Add()
//{
//	operation = '+';
//	auto input = ui.GetValues();
//	auto res = logic.Add(input.first, input.second);
//	ui.SetResult(res.str());
//	auto his = ComposeHistory(input.first, input.second, operation, res);
//	history.push_back(his);
//	ui.AddHistory(his);
//}
//
//void Controller::Sub()
//{
//	operation = '-';
//	auto input = ui.GetValues();
//	auto res = logic.Sub(input.first, input.second);
//	ui.SetResult(res.str());
//	auto his = ComposeHistory(input.first, input.second, operation, res);
//	history.push_back(his);
//	ui.AddHistory(his);
//}
//
//void Controller::Mul()
//{
//	operation = '*';
//	auto input = ui.GetValues();
//	auto res = logic.Mul(input.first, input.second);
//	ui.SetResult(res.str());
//	auto his = ComposeHistory(input.first, input.second, operation, res);
//	history.push_back(his);
//	ui.AddHistory(his);
//}
//
//void Controller::Div()
//{
//	operation = '/';
//	auto input = ui.GetValues();
//	auto res = logic.Div(input.first, input.second);
//	ui.SetResult(res.str());
//	auto his = ComposeHistory(input.first, input.second, operation, res);
//	history.push_back(his);
//	ui.AddHistory(his);
//}
//
//void Controller::Mod()
//{
//	operation = '%';
//	auto input = ui.GetValues();
//	auto res = logic.Mod(input.first, input.second);
//	ui.SetResult(res.str());
//	auto his = ComposeHistory(input.first, input.second, operation, res);
//	history.push_back(his);
//	ui.AddHistory(his);
//}
//
//void Controller::Exp()
//{
//	operation = '^';
//	auto input = ui.GetValues();
//	auto res = logic.Exp(input.first, input.second);
//	ui.SetResult(res.str());
//	auto his = ComposeHistory(input.first, input.second, operation, res);
//	history.push_back(his);
//	ui.AddHistory(his);
//}
