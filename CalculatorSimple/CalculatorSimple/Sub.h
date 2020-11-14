#pragma once
#include "Expression.h"
class Sub : public Expression
{
public:
	Sub(Expression* leftExpression, Expression* rightExpression);
	double Evaluate() override;
	ostream& Print(ostream& out) override;
	~Sub();

	Expression* expressionLeft;
	Expression* expressionRight;
};
