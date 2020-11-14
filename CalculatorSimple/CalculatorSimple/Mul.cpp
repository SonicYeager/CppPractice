#include "Mul.h"


Mul::Mul(Expression* leftExpression, Expression* rightExpression)
	: expressionLeft(leftExpression)
	, expressionRight(rightExpression)
{
	this->value = Evaluate();
}

double Mul::Evaluate()
{
	return this->expressionLeft->value * this->expressionRight->value;
}

ostream& Mul::Print(ostream& out)
{
	return expressionLeft->Print(out) << " * " << expressionRight->Print(out) << ' ';
}


Mul::~Mul()
{
	delete expressionLeft;
	delete expressionRight;
}
