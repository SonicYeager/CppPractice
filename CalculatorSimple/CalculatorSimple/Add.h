#pragma once
#include "Expression.h"
class Add : public Expression
{
public:
	Add(Expression* leftExpression, Expression* rightExpression);
	double Evaluate() override; //m�chte double zur verf�gung stellen!
	ostream& Print(ostream& out) override; //m�chte string? vern�nftig repr�sentieren
	~Add();

	Expression* expressionLeft;
	Expression* expressionRight;
};
