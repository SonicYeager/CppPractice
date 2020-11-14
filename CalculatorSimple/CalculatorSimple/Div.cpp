#include "Div.h"


Div::Div(Expression* leftExpression, Expression* rightExpression)
	: expressionLeft(leftExpression)
	, expressionRight(rightExpression)
{
	this->value = Evaluate();
}

double Div::Evaluate()
{
	return this->expressionLeft->value / this->expressionRight->value;
}

ostream& Div::Print(ostream& out)
{
	return out << ' ' << expressionLeft->Print(out) << " / " << expressionRight->Print(out) << ' ';
}

Div::~Div()
{
	delete expressionLeft;
	delete expressionRight;
}
