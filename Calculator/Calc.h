#pragma once
#include "Contracts.h"

class Calc : public Logic
{
public:
	std::stringstream Add(double, double) const override;
	std::stringstream Sub(double, double) const override;
	std::stringstream Mul(double, double) const override;
	std::stringstream Div(double, double) const override;
	std::stringstream Mod(double, double) const override;
	std::stringstream Exp(double, double) const override;
};