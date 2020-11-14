#pragma once
#include "Expression.h"
class Mul : public Expression
{
public:
	Mul(Expression* leftExpression, Expression* rightExpression);
	double Evaluate() override;
	ostream& Print(ostream& out) override;
	~Mul();

	Expression* expressionLeft;
	Expression* expressionRight;
};
