#pragma once
#include "Expression.h"
class Div : public Expression
{
public:
	Div(Expression* leftExpression, Expression* rightExpression);
	double Evaluate() override;
	ostream& Print(ostream& out) override;
	~Div();

	Expression* expressionLeft;
	Expression* expressionRight;
};
