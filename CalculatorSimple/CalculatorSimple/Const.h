#pragma once
#include "Expression.h"
class Const : public Expression
{
public:
	Const(double value)
		: Expression(value){};
	double Evaluate() override;
	~Const(){};
};
