#pragma once
#include <sstream>
#include <functional>

using CalcEvent = std::function<void()>;

class Logic
{
public:
	virtual std::stringstream Add(double, double) const = 0;
	virtual std::stringstream Sub(double, double) const = 0;
	virtual std::stringstream Mul(double, double) const = 0;
	virtual std::stringstream Div(double, double) const = 0;
	virtual std::stringstream Mod(double, double) const = 0;
	virtual std::stringstream Exp(double, double) const = 0;
};

class Ui
{
public:
	virtual void Init() = 0;
	virtual void SetResult(const std::string&) = 0;
	virtual void AddHistory(const std::string&) = 0;
	virtual std::pair<double, double> GetValues() = 0;

	CalcEvent onAdd = {};
	CalcEvent onSub = {};
	CalcEvent onMul = {};
	CalcEvent onDiv = {};
	CalcEvent onMod = {};
	CalcEvent onExp = {};
	CalcEvent onNum = {};
};