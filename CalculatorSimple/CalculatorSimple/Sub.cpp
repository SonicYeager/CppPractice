#include "Sub.h"


Sub::Sub(Expression* leftExpression, Expression* rightExpression)
	: expressionLeft(leftExpression)
	, expressionRight(rightExpression)
{
	this->value = Evaluate();
}

double Sub::Evaluate()
{
	return this->expressionLeft->value - this->expressionRight->value;
}

ostream& Sub::Print(ostream& out)
{
	
	return out << ' ' << expressionLeft->Print(out) << " - " << expressionRight->Print(out) << ' ';
	
}

Sub::~Sub()
{
	delete expressionLeft;
	delete expressionRight;
}
