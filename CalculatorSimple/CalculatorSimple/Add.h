#pragma once
#include "Expression.h"
class Add : public Expression
{
public:
	Add(Expression* leftExpression, Expression* rightExpression);
	double Evaluate() override; //möchte double zur verfügung stellen!
	ostream& Print(ostream& out) override; //möchte string? vernünftig repräsentieren
	~Add();

	Expression* expressionLeft;
	Expression* expressionRight;
};
