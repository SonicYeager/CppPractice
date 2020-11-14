#pragma once
#include "Expression.h"
class Result : public Expression
{
public:
	Result(Expression* expression);
	~Result();

	double Evaluate() override;
	ostream& Print(ostream& out) override;

	void operator=(Expression* expression);

	Expression* expression;
};
